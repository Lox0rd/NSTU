# Часть 1. Загрузка и предобработка данных

# Загружаем необходимые пакеты
library(vcd)
library(ggplot2)
library(dplyr)

# Загрузка данных из файла train.csv
titanic_data <- read.csv("train.csv")

# Проверка структуры данных: первые 6 строк
head(titanic_data, 6)

# Общая информация о датасете
str(titanic_data)
summary(titanic_data)

# Анализ пропусков: определение столбцов с пропущенными значениями и их количества
missing_values <- colSums(is.na(titanic_data))
print(missing_values)

# Обработка пропусков
# Замена пропущенных значений в столбце Age на медианное значение возраста
median_age <- median(titanic_data$Age, na.rm = TRUE)
titanic_data$Age[is.na(titanic_data$Age)] <- median_age

# Удаление строк с пропусками в столбце Embarked
titanic_data <- titanic_data[!is.na(titanic_data$Embarked), ]

# Приведение типов
# Преобразование столбцов Survived, Pclass, Sex в факторные переменные
titanic_data$Survived <- factor(titanic_data$Survived,
                                labels = c("Погиб", "Выжил"))
titanic_data$Pclass <- factor(titanic_data$Pclass)
titanic_data$Sex <- factor(titanic_data$Sex)

# Убедимся, что Age и Fare имеют тип numeric
titanic_data$Age <- as.numeric(titanic_data$Age)
titanic_data$Fare <- as.numeric(titanic_data$Fare)

# Создание нового столбца AgeGroup для категоризации возраста
titanic_data <- titanic_data %>%
  mutate(AgeGroup = case_when(
    Age < 18 ~ "Ребёнок",
    Age >= 18 & Age < 60 ~ "Взрослый",
    Age >= 60 ~ "Пожилой"
  ))
titanic_data$AgeGroup <- factor(titanic_data$AgeGroup,
                                levels = c("Ребёнок", "Взрослый", "Пожилой"))

# Часть 2. Построение мозаичной диаграммы

# Настройка цветовой схемы: зелёный для выживших, красный для погибших
survival_colors <- c("Погиб" = "red", "Выжил" = "green")

# Построение мозаичной диаграммы с помощью функции mosaic() из пакета vcd
mosaic(~ Pclass + Sex + Survived, 
       data = titanic_data,
       shade = TRUE,
       gp = shading_hcl,
       gp_args = list(interpolate = c(1, 2, 3, 4)),
       main = "Мозаичная диаграмма: выживаемость по классу и полу",
       # --- Новые параметры для сжатия ---
       labeling_args = list(
         abbreviate = 3,           # Сокращаем названия до 3 букв
         check_overlap = TRUE,     # Скрываем перекрывающиеся метки
         rot_labels = 45           # Наклоняем метки для экономии места
       ),
       cex = 0.3
)


# Сохранение мозаичной диаграммы в формате PNG с разрешением 300 DPI
png("mosaic_titanic.png", width = 3200, height = 1600, res = 300)
mosaic(~ Pclass + Sex + Survived, 
       data = titanic_data,
       shade = TRUE,
       gp = shading_hcl,
       gp_args = list(interpolate = c(1, 2, 3, 4)),
       main = "Мозаичная диаграмма: выживаемость по классу и полу",
       # --- Новые параметры для сжатия ---
       labeling_args = list(
         abbreviate = 3,           # Сокращаем названия до 3 букв
         check_overlap = TRUE,     # Скрываем перекрывающиеся метки
         rot_labels = 45           # Наклоняем метки для экономии места
       ),
       cex = 0.3
)

dev.off()

# Часть 3. Построение пузырьковой диаграммы

# Масштабирование размера пузырьков (делим возраст на 10 для более адекватного отображения)
titanic_data$Size <- titanic_data$Age / 10

# Построение пузырьковой диаграммы с помощью ggplot2
bubble_plot <- ggplot(titanic_data, aes(x = Age, y = Fare, size = Size, color = Survived)) +
  geom_point(alpha = 0.6) +  # Прозрачность точек
  scale_color_manual(values = survival_colors) +  # Задаём цвета для выживаемости
  geom_smooth(method = "loess", se = FALSE, color = "black") +  # Сглаживающая линия
  labs(title = "Пузырьковая диаграмма: возраст, плата за проезд и выживаемость",
       x = "Возраст (лет)",
       y = "Плата за проезд (USD)") +
  theme_minimal()

# Отображение графика
print(bubble_plot)

# Сохранение пузырьковой диаграммы в формате PNG с разрешением 300 DPI
ggsave("bubble_titanic.png", plot = bubble_plot,
       width = 8, height = 6, dpi = 300)

# Часть 4. Интерпретация результатов

# Краткий отчёт с выводами по результатам анализа

cat("Краткий отчёт по результатам анализа выживаемости пассажиров «Титаника»:\n\n")

cat("1. Мозаичная диаграмма показывает, что:\n")
cat("   - Женщины имели значительно более высокую выживаемость во всех классах.\n")
cat("   - В первом классе выживаемость была выше, чем в третьем, особенно среди мужчин.\n")
cat("   - Доля выживших женщин в первом классе была максимальной, а мужчин в третьем классе — минимальной.\n\n")

cat("2. Пузырьковая диаграмма позволяет отметить:\n")
cat("   - Кластер пассажиров с низкой платой за проезд и возрастом 20–40 лет — преимущественно погибшие.\n")
cat("   - Выбросы с высокой платой за проезд (более 500 USD) — все выжили, это пассажиры первого класса.\n")
cat("   - Общая тенденция: пассажиры с более высокой платой за проезд чаще выживали.\n\n")

cat("3. Основные выводы о факторах выживаемости:\n")
cat("   - Пол: женщины имели приоритет при спасении, что резко повышало их шансы на выживание.\n")
cat("   - Класс каюты: пассажиры первого класса выживали чаще, вероятно, из-за расположения кают ближе к палубе и приоритета при эвакуации.\n")
cat("   - Стоимость билета: высокая плата за проезд коррелирует с выживаемостью, что связано с классом каюты и социальным статусом.\n")
