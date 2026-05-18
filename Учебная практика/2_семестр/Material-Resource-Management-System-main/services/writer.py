import pandas as pd

def writer_data(summary_table, smeta_material, smeta_value, output_path):
    with pd.ExcelWriter(output_path, engine='openpyxl') as writer:
        summary_table.to_excel(writer, sheet_name='Ведомость материалов', index=False)
        
        smeta_material.to_excel(writer, sheet_name='Смета материалов', index=False)
        
        smeta_df = pd.DataFrame({'Общая сумма': [smeta_value]})
        smeta_df.to_excel(writer, sheet_name='Денежная смета', index=False)
