import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os
import math

# Создаём папку для результатов, если её нет
results_dir = 'results'
os.makedirs(results_dir, exist_ok=True)

# Настройка стиля графиков
plt.style.use('seaborn-v0_8')
sns.set_palette("husl")

# Чтение данных из CSV-файла
df = pd.read_csv('performance_results.csv')

# Преобразуем AverageTimeMs в числовой формат
df['AverageTimeMs'] = pd.to_numeric(df['AverageTimeMs'], errors='coerce')

# Сводная таблица для вывода в консоль
print("\nСВОДНАЯ ТАБЛИЦА РЕЗУЛЬТАТОВ:")
print("=" * 80)
pivot_table = df.pivot_table(
    values='AverageTimeMs',
    index=['Size', 'SearchType'],
    columns='Algorithm',
    aggfunc='first'
)
print(pivot_table.round(4))

# Сохраняем сводную таблицу
pivot_table.to_csv(os.path.join(results_dir, 'summary_results.csv'))

# Фильтруем данные по типу поиска
successful_search = df[df['SearchType'] == 'Existing']
failed_search = df[df['SearchType'] == 'Missing']
algorithms = successful_search['Algorithm'].unique()

# --- 1. Успешный поиск ---
fig1, ax1 = plt.subplots(figsize=(12, 8))
for algorithm in algorithms:
    data = successful_search[successful_search['Algorithm'] == algorithm]
    if not data.empty:  # Защита от пустых данных
        ax1.plot(data['Size'], data['AverageTimeMs'], 
                marker='o', linewidth=2, label=algorithm)

ax1.set_xlabel('Размер данных (количество элементов)')
ax1.set_ylabel('Среднее время поиска, мс')
ax1.set_title('Зависимость времени успешного поиска от размера данных')
ax1.legend()
ax1.grid(True, alpha=0.3)
ax1.set_xscale('log')
ax1.set_yscale('log')  # ВАЖНО: логарифмическая шкала по Y

fig1.savefig(os.path.join(results_dir, 'successful_search_comparison.png'), dpi=300, bbox_inches='tight')
plt.close(fig1)

# --- 2. Неуспешный поиск ---
fig2, ax2 = plt.subplots(figsize=(12, 8))
for algorithm in algorithms:
    data = failed_search[failed_search['Algorithm'] == algorithm]
    if not data.empty:
        ax2.plot(data['Size'], data['AverageTimeMs'], 
                marker='s', linewidth=2, label=algorithm)

ax2.set_xlabel('Размер данных (количество элементов)')
ax2.set_ylabel('Среднее время поиска, мс')
ax2.set_title('Зависимость времени безуспешного поиска от размера данных')
ax2.legend()
ax2.grid(True, alpha=0.3)
ax2.set_xscale('log')
ax2.set_yscale('log')

fig2.savefig(os.path.join(results_dir, 'failed_search_comparison.png'), dpi=300, bbox_inches='tight')
plt.close(fig2)

# --- 3. Попарное сравнение (успешный vs неуспешный) ---
for algorithm in algorithms:
    fig_pair, ax_pair = plt.subplots(figsize=(10, 6))
    
    succ_data = successful_search[successful_search['Algorithm'] == algorithm]
    fail_data = failed_search[failed_search['Algorithm'] == algorithm]
    
    if not succ_data.empty:
        ax_pair.plot(succ_data['Size'], succ_data['AverageTimeMs'], 
                    marker='o', linewidth=2, label='Успешный поиск')
    if not fail_data.empty:
        ax_pair.plot(fail_data['Size'], fail_data['AverageTimeMs'], 
                    marker='s', linewidth=2, label='Безуспешный поиск')

    ax_pair.set_xlabel('Размер данных (количество элементов)')
    ax_pair.set_ylabel('Среднее время поиска, мс')
    ax_pair.set_title(f'Сравнение поиска для {algorithm}')
    ax_pair.legend()
    ax_pair.grid(True, alpha=0.3)
    ax_pair.set_xscale('log')
    ax_pair.set_yscale('log')
    plt.tight_layout()

    fig_pair.savefig(os.path.join(results_dir, f'comparison_{algorithm}.png'), dpi=300, bbox_inches='tight')
    plt.close(fig_pair)

# --- 4. Сравнение с теорией (без произвольной нормализации) ---
fig_theory, ax_theory = plt.subplots(figsize=(12, 8))
sizes = sorted(df['Size'].unique())

# Чистые теоретические кривые (без умножения на константы)
n_curve = sizes  # O(n)
logn_curve = [math.log(s) for s in sizes]  # O(log n)

const_curve = [1 for _ in sizes] # O(1) — константа > 0 для логарифмической шкалы

ax_theory.plot(sizes, n_curve, '--', label='Теоретическая O(n)', alpha=0.7)
ax_theory.plot(sizes, logn_curve, '--', label='Теоретическая O(log n)', alpha=0.7)
ax_theory.plot(sizes, const_curve, '--', label='Теоретическая O(1)', alpha=0.7)

# Практические данные (среднее по всем типам поиска)
for algorithm in algorithms:
    combined_data = df[df['Algorithm'] == algorithm].groupby('Size')['AverageTimeMs'].mean()
    if not combined_data.empty:
        ax_theory.plot(combined_data.index, combined_data.values,
                      marker='o', linewidth=2, label=f'Практический ({algorithm})')

ax_theory.set_xlabel('Размер данных (количество элементов)')
ax_theory.set_ylabel('Время поиска, мс')
ax_theory.set_title('Сравнение практических результатов с теоретическими оценками')
ax_theory.legend()
ax_theory.grid(True, alpha=0.3)
ax_theory.set_xscale('log')
ax_theory.set_yscale('log')  # Ключевое изменение

fig_theory.savefig(os.path.join(results_dir, 'theory_vs_practice.png'), dpi=300, bbox_inches='tight')
plt.close(fig_theory)

print("\nГрафики успешно сохранены в папку 'results'.")
