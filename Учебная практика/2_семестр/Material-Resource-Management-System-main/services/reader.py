import pandas as pd


def parcing(file_path):
    sheets = pd.read_excel(file_path, sheet_name=['Материалы', 'Цены'], engine='openpyxl')

    materials_df = sheets['Материалы']
    prices_df = sheets['Цены']
    
    materials_df.columns = ['Наименование', 'Тип', 'Материал', 'количество', 'Ед.изм']
    prices_df.columns = ['Материал', 'Цена']
    
    # Объединяем таблицы по столбцу 'Материал' — берём только совпадающие записи
    result_df = pd.merge(materials_df, prices_df, on='Материал', how='inner')
    
    return result_df
