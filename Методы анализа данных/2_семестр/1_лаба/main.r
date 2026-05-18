# Установка и загрузка необходимых пакетов
if (!require(nortest)) install.packages("nortest")
if (!require(corrplot)) install.packages("corrplot")
if (!require(ppcor)) install.packages("ppcor")
if (!require(GGally)) install.packages("GGally")
if (!require(ggplot2)) install.packages("ggplot2")
if (!require(rcompanion)) install.packages("rcompanion")

library(nortest)
library(corrplot)
library(ppcor)
library(GGally)
library(ggplot2)
library(rcompanion)

# Загрузка данных (замените "data_variant15.csv" на путь к вашему файлу)
data <- read.csv("data_variant15.csv", stringsAsFactors = FALSE)

# Предварительный просмотр данных
head(data)
str(data)
summary(data)
# Проверка на пропущенные значения
sum(is.na(data))

# Разделение данных на группы
group1 <- data[data$Group == 1, ]
group2 <- data[data$Group == 2, ]

# Описательная статистика для количественных переменных по группам
summary_group1 <- summary(group1[, c("Age", "Work.experience", "Average.income", "Professional.specialization", "Average.number.of.pages", "Activity.level.score")])
summary_group2 <- summary(group2[, c("Age", "Work.experience", "Average.income", "Professional.specialization", "Average.number.of.pages", "Activity.level.score")])

print("Описательная статистика для группы 1:")
print(summary_group1)
print("Описательная статистика для группы 2:")
print(summary_group2)
# Функция для проверки нормальности несколькими критериями
check_normality <- function(x, group_name) {
  cat("\nПроверка нормальности для группы", group_name, "\n")
  cat("Критерий Шапиро–Уилка: ", shapiro.test(x)$p.value, "\n")
  cat("Критерий Андерсона–Дарлинга: ", ad.test(x)$p.value, "\n")
  cat("Критерий Крамера–Мизеса: ", cvm.test(x)$p.value, "\n")
}

# Проверка для признака Age
check_normality(group1$Age, "1 (признак Age)")
check_normality(group2$Age, "2 (признак Age)")

# Построение гистограмм с кривой нормального распределения
plot_histogram_with_normal <- function(data, variable, group_name) {
  mean_val <- mean(data[[variable]])
  sd_val <- sd(data[[variable]])
  
  ggplot(data, aes(x = !!sym(variable))) +
    geom_histogram(aes(y = ..density..), bins = 20, fill = "lightblue", color = "black") +
    stat_function(fun = dnorm, args = list(mean = mean_val, sd = sd_val),
                  color = "red", size = 1) +
    labs(title = paste("Гистограмма и нормальное распределение (", group_name, ")"),
         x = variable, y = "Плотность") +
    theme_minimal()
}

plot_histogram_with_normal(group1, "Age", "Группа 1")
plot_histogram_with_normal(group2, "Age", "Группа 2")

# Ручной расчёт χ² и Крамера–Мизеса для признака Age в группе 1
# χ² тест
observed <- table(cut(group1$Age, breaks = 10))
expected <- rep(length(group1$Age) / 10, 10)
chi_square_stat <- sum((observed - expected)^2 / expected)
p_value_chi <- 1 - pchisq(chi_square_stat, df = 9)
cat("Ручной расчёт χ² для Age (группа 1): статистика =", chi_square_stat, ", p-значение =", p_value_chi, "\n")

# Крамер–Мизес (упрощённый ручной расчёт)
n <- length(group1$Age)
sorted_data <- sort(group1$Age)
mean_age <- mean(sorted_data)
sd_age <- sd(sorted_data)

# Расчёт теоретической функции распределения
F_empirical <- (1:n) / n
F_theoretical <- pnorm(sorted_data, mean = mean_age, sd = sd_age)

# Статистика Крамера–Мизеса
CM_statistic <- sum((F_empirical - F_theoretical)^2) / n + 1 / (12 * n)
cat("Ручной расчёт Крамера–Мизеса для Age (группа 1): статистика =", CM_statistic, "\n")
# Выбор количественных переменных
quantitative_vars <- c("Age", "Work.experience", "Average.income", "Professional.specialization",
                       "Average.number.of.pages", "Activity.level.score")

# Коэффициенты корреляции для группы 1
cor_pearson_g1 <- cor(group1[quantitative_vars], method = "pearson")
cor_spearman_g1 <- cor(group1[quantitative_vars], method = "spearman")
cor_kendall_g1 <- cor(group1[quantitative_vars], method = "kendall")

# Для группы 2
cor_pearson_g2 <- cor(group2[quantitative_vars], method = "pearson")
cor_spearman_g2 <- cor(group2[quantitative_vars], method = "spearman")
cor_kendall_g2 <- cor(group2[quantitative_vars], method = "kendall")

# Визуализация корреляционных матриц
corrplot(cor_pearson_g1, method = "color", title = "Матрица корреляции Пирсона (Группа 1)")
corrplot(cor_spearman_g1, method = "color", title = "Матрица корреляции Спирмена (Группа 1)")

# Ручной расчёт коэффициентов Пирсона и Спирмена для пары Age и Work.experience в группе 1
x <- group1$Age
y <- group1$Work.experience
n <- length(x)

# Пирсон
pearson_manual <- sum((x - mean(x)) * (y - mean(y))) / (sqrt(sum((x - mean(x))^2)) * sqrt(sum((y - mean(y))^2)))
cat("Ручной расчёт коэффициента Пирсона для Age и Work.experience (группа 1):", pearson_manual, "\n")

# Спирмен (через ранги)
rank_x <- rank(x)
rank_y <- rank(y)
spearman_manual <- 1 - (6 * sum((rank_x - rank_y)^2)) / (n * (n^2 - 1))
cat("Ручной расчёт коэффициента Спирмена для Age и Work.experience (группа 1):", spearman_manual, "\n")

# Проверка значимости коэффициента Пирсона через t‑критерий
t_stat <- pearson_manual * sqrt(n - 2) / sqrt(1 - pearson_manual^2)
p_value <- 2 * pt(abs(t_stat), df = n - 2, lower.tail = FALSE)
cat("t‑статистика:", t_stat, "p‑значение:", p_value, "\n")

# Частные коэффициенты корреляции (пример для Age, Work.experience, контролируя Average.income)
partial_cor <- pcor(group1[, c("Age", "Work.experience", "Average.income")], method = "pearson")
print("Частные коэффициенты корреляции:")
print(partial_cor$estimate)
# Однофакторный ANOVA (пример: влияние Gender на Age)
model_anova <- aov(Age ~ Gender, data = data)
summary(model_anova)

# Критерий Краскела–Уоллиса (непараметрический аналог ANOVA)
kruskal.test(Age ~ Gender, data = data)

# Ручной расчёт ANOVA для Gender и Age (продолжение)
# Группируем данные
group_male <- data[data$Gender == "Male", "Age"]
group_female <- data[data$Gender == "Female", "Age"]

# Описательные статистики
n1 <- length(group_male)
n2 <- length(group_female)
mean1 <- mean(group_male)
mean2 <- mean(group_female)
var1 <- var(group_male)
var2 <- var(group_female)

# Общая средняя
grand_mean <- mean(data$Age)

# Сумма квадратов между группами (SSB)
SSB <- n1 * (mean1 - grand_mean)^2 + n2 * (mean2 - grand_mean)^2

# Сумма квадратов внутри групп (SSW)
SSW <- sum((group_male - mean1)^2) + sum((group_female - mean2)^2)

# Степени свободы
df_between <- 1  # k - 1, где k — число групп
df_within <- n1 + n2 - 2

# Средние квадраты
MSB <- SSB / df_between
MSW <- SSW / df_within

# F‑статистика
F_stat <- MSB / MSW

# p‑значение
p_value_anova <- 1 - pf(F_stat, df_between, df_within)

cat("Ручной расчёт ANOVA:\n")
cat("SSB =", SSB, ", SSW =", SSW, "\n")
cat("MSB =", MSB, ", MSW =", MSW, "\n")
cat("F‑статистика =", F_stat, ", p‑значение =", p_value_anova, "\n")
# Создание таблицы сопряжённости для Gender и Activity.level.level
contingency_table <- table(data$Gender, data$Activity.level.level)
print("Таблица сопряжённости Gender × Activity.level.level:")
print(contingency_table)

# Критерий χ²
chi_square_test <- chisq.test(contingency_table)
cat("Критерий χ²:\n")
print(chi_square_test)

# Точный критерий Фишера
fisher_test <- fisher.test(contingency_table)
cat("Точный критерий Фишера:\n")
print(fisher_test)

# Ручной расчёт χ² для таблицы сопряжённости
# Ожидаемые частоты
expected_freq <- outer(rowSums(contingency_table), colSums(contingency_table)) / sum(contingency_table)

# Расчёт χ² статистики
chi_square_manual <- sum((contingency_table - expected_freq)^2 / expected_freq)

# Степени свободы
df_chi <- (nrow(contingency_table) - 1) * (ncol(contingency_table) - 1)

# p‑значение
p_value_chi_manual <- 1 - pchisq(chi_square_manual, df_chi)

cat("Ручной расчёт χ²:\n")
cat("χ² =", chi_square_manual, ", df =", df_chi, ", p‑значение =", p_value_chi_manual, "\n")
# Преобразование качественных переменных в факторы для ggpairs
data_factors <- data
data_factors$Gender <- as.factor(data_factors$Gender)
data_factors$Activity.level.level <- as.factor(data_factors$Activity.level.level)
data_factors$Group <- as.factor(data_factors$Group)

# Построение матричного графика
matrix_plot <- ggpairs(
  data_factors,
  columns = c("Age", "Work.experience", "Average.income", "Professional.specialization",
              "Average.number.of.pages", "Activity.level.score"),
  mapping = aes(color = Group),
  upper = list(continuous = "cor"),
  lower = list(continuous = "points"),
  title = "Матричный график взаимосвязей признаков"
)

print(matrix_plot)
# Автоматизированный вывод основных результатов
cat("\n=== ОБЩИЕ ВЫВОДЫ ===\n")

# Нормальность распределения
cat("1. Проверка нормальности:\n")
if (shapiro.test(group1$Age)$p.value > 0.05) {
  cat("   Возраст в группе 1 распределён нормально\n")
} else {
  cat("   Возраст в группе 1 не распределён нормально\n")
}

if (shapiro.test(group2$Age)$p.value > 0.05) {
  cat("   Возраст в группе 2 распределён нормально\n")
} else {
  cat("   Возраст в группе 2 не распределён нормально\n")
}

# Корреляции
cat("2. Корреляционный анализ:\n")
cat("   Наиболее сильная корреляция в группе 1: ",
    names(which.max(abs(cor_pearson_g1[upper.tri(cor_pearson_g1)]))), "\n")
cat("   Наиболее сильная корреляция в группе 2: ",
    names(which.max(abs(cor_pearson_g2[upper.tri(cor_pearson_g2)]))), "\n")

# Связь качественных и количественных признаков
cat("3. Связь качественных и количественных признаков:\n")
if (p_value_anova < 0.05) {
  cat("   Есть статистически значимая связь между полом и возрастом\n")
} else {
  cat("   Нет статистически значимой связи между полом и возрастом\n")
}

# Анализ таблиц сопряжённости
cat("4. Анализ таблиц сопряжённости:\n")
if (p_value_chi_manual < 0.05) {
  cat("   Есть статистически значимая связь между полом и уровнем активности\n")
} else {
  cat("   Нет статистически значимой связи между полом и уровнем активности\n")
}

cat("\nРекомендации:\n")
cat("- Для групп с ненормальным распределением использовать непараметрические методы\n")
cat("- Выявленные корреляции требуют дополнительного исследования причинно‑следственных связей\n")
cat("- Значимые различия между группами могут быть использованы для персонализации услуг\n")
