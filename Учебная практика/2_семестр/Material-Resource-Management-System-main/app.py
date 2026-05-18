from flask import Flask, render_template, request, send_file, redirect, url_for
import pandas as pd
import os
from werkzeug.utils import secure_filename
from services.processor import create_smeta_materials, create_summary_table, smeta
from services.reader import parcing
from services.writer import writer_data

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'uploads'
app.config['RESULT_FOLDER'] = 'results'
app.config['ALLOWED_EXTENSIONS'] = {'xlsx', 'xls', 'csv'}

# Создаём папки для загрузок и результатов
os.makedirs(app.config['UPLOAD_FOLDER'], exist_ok=True)
os.makedirs(app.config['RESULT_FOLDER'], exist_ok=True)

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in app.config['ALLOWED_EXTENSIONS']

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return redirect(request.url)
    
    file = request.files['file']
    
    if file.filename == '':
        return redirect(request.url)
    
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)
        
        # Применяем функции к загруженному файлу
        try:
            # Парсинг файла в DataFrame
            df = parcing(filepath)
            
            summary_table = create_summary_table(df)
            smeta_material = create_smeta_materials(df)
            smeta_value = smeta(df)
            
            # Создаём выходной файл
            output_filename = f'result_{filename}'
            output_path = os.path.join(app.config['RESULT_FOLDER'], output_filename)
            
            writer_data(summary_table, smeta_material, smeta_value, output_path)
            
            return redirect(url_for('result', filename=output_filename))
            
        except Exception as e:
            return f"Ошибка при обработке файла: {str(e)}"
    
    return 'Неверный формат файла'

@app.route('/result/<filename>')
def result(filename):
    file_path = os.path.join(app.config['RESULT_FOLDER'], filename)
    if os.path.exists(file_path):
        return render_template('result.html', filename=filename)
    else:
        return 'Файл не найден', 404

@app.route('/download/<filename>')
def download_file(filename):
    file_path = os.path.join(app.config['RESULT_FOLDER'], filename)
    if os.path.exists(file_path):
        return send_file(file_path, as_attachment=True)
    else:
        return 'Файл для скачивания не найден', 404

if __name__ == '__main__':
    app.run(debug=True)
