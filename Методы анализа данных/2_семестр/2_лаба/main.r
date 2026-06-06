# =========================================================
# ЛАБОРАТОРНАЯ РАБОТА
# Анализ взаимосвязей между признаками
# Вариант 15
# =========================================================

# -----------------------------
# УСТАНОВКА И ПОДКЛЮЧЕНИЕ ПАКЕТОВ
# -----------------------------

# install.packages(c(
#   "tidyverse",
#   "nortest",
#   "corrplot",
#   "ppcor",
#   "GGally",
#   "ggplot2",
#   "rcompanion",
#   "psych",
#   "DescTools"
# ))

library(tidyverse)
library(nortest)
library(corrplot)
library(ppcor)
library(GGally)
library(ggplot2)
library(rcompanion)
library(psych)
library(DescTools)

# -----------------------------
# ЗАГРУЗКА ДАННЫХ
# -----------------------------

# Указать путь к CSV
df <- read.csv("variant15.csv", stringsAsFactors = TRUE)

# Просмотр структуры
str(df)

# Первые строки
head(df)

# Размерность
dim(df)

# Общая статистика
summary(df)

# Проверка пропусков
colSums(is.na(df))

# -----------------------------
# ПЕРЕИМЕНОВАНИЕ СТОЛБЦОВ
# -----------------------------

colnames(df) <- c(
  "Group",
  "Gender",
  "Age",
  "WorkExperience",
  "AverageIncome",
  "ProfessionalSpecialization",
  "AveragePages",
  "ActivityScore",
  "ActivityLevel"
)

# -----------------------------
# ПРЕОБРАЗОВАНИЕ ТИПОВ
# -----------------------------

df$Group <- as.factor(df$Group)
df$Gender <- as.factor(df$Gender)
df$ActivityLevel <- as.factor(df$ActivityLevel)

# -----------------------------
# РАЗДЕЛЕНИЕ НА ГРУППЫ
# -----------------------------

g1 <- df %>% filter(Group == levels(df$Group)[1])
g2 <- df %>% filter(Group == levels(df$Group)[2])

# -----------------------------
# КОЛИЧЕСТВЕННЫЕ ПРИЗНАКИ
# -----------------------------

num_cols <- c(
  "Age",
  "WorkExperience",
  "AverageIncome",
  "ProfessionalSpecialization",
  "AveragePages",
  "ActivityScore"
)

# =========================================================
# 1. ПРОВЕРКА НОРМАЛЬНОСТИ
# =========================================================

# -----------------------------
# ФУНКЦИЯ ПРОВЕРКИ НОРМАЛЬНОСТИ
# -----------------------------

norm_tests <- function(data, var_name) {

  x <- data[[var_name]]

  cat("\n====================================\n")
  cat("ПРИЗНАК:", var_name, "\n")
  cat("====================================\n")

  # Шапиро-Уилк
  print(shapiro.test(x))

  # Крамер-Мизес
  print(cvm.test(x))

  # Андерсон-Дарлинг
  print(ad.test(x))

  # Хи-квадрат
  print(DescTools::GTest(table(cut(x, breaks = 6))))
}

# -----------------------------
# ГРУППА 1
# -----------------------------

cat("\n\n############ ГРУППА 1 ############\n")

for(v in num_cols){
  norm_tests(g1, v)
}

# -----------------------------
# ГРУППА 2
# -----------------------------

cat("\n\n############ ГРУППА 2 ############\n")

for(v in num_cols){
  norm_tests(g2, v)
}

# =========================================================
# ГИСТОГРАММЫ
# =========================================================

for(v in num_cols){

  ggplot(df, aes_string(x = v)) +
    geom_histogram(
      aes(y = ..density..),
      bins = 10,
      fill = "skyblue",
      color = "black"
    ) +
    stat_function(
      fun = dnorm,
      args = list(
        mean = mean(df[[v]], na.rm = TRUE),
        sd = sd(df[[v]], na.rm = TRUE)
      ),
      color = "red",
      linewidth = 1
    ) +
    facet_wrap(~Group) +
    ggtitle(paste("Гистограмма:", v)) +
    theme_minimal() -> p

  print(p)
}

# =========================================================
# РУЧНОЙ РАСЧЁТ χ² ДЛЯ НОРМАЛЬНОСТИ
# =========================================================

x <- g1$Age

# Количество интервалов
k <- 6

# Интервалы
br <- seq(min(x), max(x), length.out = k + 1)

# Наблюдаемые частоты
obs <- table(cut(x, breaks = br))

# Параметры нормального распределения
mu <- mean(x)
sigma <- sd(x)

# Теоретические вероятности
p <- diff(pnorm(br, mean = mu, sd = sigma))

# Ожидаемые частоты
exp_freq <- length(x) * p

# χ²
chi_sq <- sum((obs - exp_freq)^2 / exp_freq)

chi_sq

# =========================================================
# РУЧНОЙ РАСЧЁТ КРАМЕРА-МЕЗЕСА
# =========================================================

x_sort <- sort(x)

n <- length(x_sort)

f0 <- pnorm(x_sort, mean = mean(x_sort), sd = sd(x_sort))

w2 <- 1/(12*n) + sum((f0 - (2*(1:n)-1)/(2*n))^2)

w2

# =========================================================
# 2. КОРРЕЛЯЦИОННЫЙ АНАЛИЗ
# =========================================================

# -----------------------------
# КОРРЕЛЯЦИОННЫЕ МАТРИЦЫ
# -----------------------------

g1_num <- g1[, num_cols]
g2_num <- g2[, num_cols]

# Пирсон
cor_g1_pearson <- cor(g1_num, method = "pearson")
cor_g2_pearson <- cor(g2_num, method = "pearson")

# Спирмен
cor_g1_spear <- cor(g1_num, method = "spearman")
cor_g2_spear <- cor(g2_num, method = "spearman")

# Кендалл
cor_g1_kend <- cor(g1_num, method = "kendall")
cor_g2_kend <- cor(g2_num, method = "kendall")

# Вывод
cor_g1_pearson
cor_g2_pearson

cor_g1_spear
cor_g2_spear

cor_g1_kend
cor_g2_kend

# =========================================================
# ТЕПЛОВАЯ КАРТА
# =========================================================

corrplot(
  cor_g1_pearson,
  method = "color",
  type = "upper",
  tl.col = "black",
  addCoef.col = "black"
)

corrplot(
  cor_g2_pearson,
  method = "color",
  type = "upper",
  tl.col = "black",
  addCoef.col = "black"
)

# =========================================================
# РУЧНОЙ РАСЧЁТ ПИРСОНА
# =========================================================

x <- g1$Age
y <- g1$AverageIncome

mx <- mean(x)
my <- mean(y)

r <- sum((x - mx)*(y - my)) /
  sqrt(sum((x - mx)^2) * sum((y - my)^2))

r

# =========================================================
# РУЧНОЙ РАСЧЁТ СПИРМЕНА
# =========================================================

rx <- rank(x)
ry <- rank(y)

d2 <- sum((rx - ry)^2)

n <- length(x)

rs <- 1 - (6*d2)/(n*(n^2 - 1))

rs

# =========================================================
# ПРОВЕРКА ЗНАЧИМОСТИ ПИРСОНА
# =========================================================

cor.test(
  g1$Age,
  g1$AverageIncome,
  method = "pearson"
)

# Ручной расчёт t-критерия

r <- cor(g1$Age, g1$AverageIncome)

n <- nrow(g1)

t_stat <- r * sqrt((n - 2)/(1 - r^2))

t_stat

# =========================================================
# ЧАСТНЫЕ КОРРЕЛЯЦИИ
# =========================================================

pcor(
  g1_num,
  method = "pearson"
)

pcor(
  g2_num,
  method = "pearson"
)

# =========================================================
# 3. ANOVA
# =========================================================

anova_model <- aov(
  AverageIncome ~ ActivityLevel,
  data = df
)

summary(anova_model)

# =========================================================
# КРАСКЕЛ-УОЛЛИС
# =========================================================

kruskal.test(
  AverageIncome ~ ActivityLevel,
  data = df
)

# =========================================================
# РУЧНОЙ РАСЧЁТ ANOVA
# =========================================================

groups <- split(df$AverageIncome, df$ActivityLevel)

all_mean <- mean(df$AverageIncome)

# Межгрупповая сумма квадратов
ss_between <- sum(
  sapply(groups, function(g){
    length(g) * (mean(g) - all_mean)^2
  })
)

# Внутригрупповая сумма квадратов
ss_within <- sum(
  sapply(groups, function(g){
    sum((g - mean(g))^2)
  })
)

k <- length(groups)
n <- nrow(df)

ms_between <- ss_between / (k - 1)
ms_within <- ss_within / (n - k)

f_value <- ms_between / ms_within

f_value

# =========================================================
# 4. ТАБЛИЦЫ СОПРЯЖЁННОСТИ
# =========================================================

tab <- table(df$Gender, df$ActivityLevel)

tab

# χ²
chisq.test(tab)

# Фишер
fisher.test(tab)

# =========================================================
# РУЧНОЙ РАСЧЁТ χ²
# =========================================================

obs <- as.matrix(tab)

row_sum <- rowSums(obs)
col_sum <- colSums(obs)

n <- sum(obs)

exp <- outer(row_sum, col_sum) / n

chi_manual <- sum((obs - exp)^2 / exp)

chi_manual

# =========================================================
# 5. МАТРИЧНЫЙ ГРАФИК GGPairs
# =========================================================

ggpairs(
  df,
  columns = c(
    "Age",
    "WorkExperience",
    "AverageIncome",
    "AveragePages",
    "ActivityScore"
  ),
  aes(color = Group, alpha = 0.5)
)

# =========================================================
# ДОПОЛНИТЕЛЬНЫЕ ОПИСАТЕЛЬНЫЕ СТАТИСТИКИ
# =========================================================

describeBy(
  df[, num_cols],
  group = df$Group
)

# =========================================================
# BOXPLOT
# =========================================================

ggplot(df,
       aes(
         x = ActivityLevel,
         y = AverageIncome,
         fill = ActivityLevel
       )) +
  geom_boxplot() +
  theme_minimal()

# =========================================================
# SCATTERPLOT
# =========================================================

ggplot(df,
       aes(
         x = Age,
         y = AverageIncome,
         color = Group
       )) +
  geom_point(size = 3) +
  geom_smooth(method = "lm", se = FALSE) +
  theme_minimal()

# =========================================================
# СОХРАНЕНИЕ РЕЗУЛЬТАТОВ
# =========================================================

write.csv(
  cor_g1_pearson,
  "correlation_group1.csv"
)

write.csv(
  cor_g2_pearson,
  "correlation_group2.csv"
)

# =========================================================
# КОНЕЦ
# =========================================================