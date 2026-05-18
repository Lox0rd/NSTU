# --- УСТАНОВКА И ПОДКЛЮЧЕНИЕ БИБЛИОТЕК ---
install.packages(c("nortest", "rcompanion", "corrplot", "ppcor", "GGally", "ggplot2"))

library(nortest)
library(corrplot)
library(ppcor)
library(GGally)
library(ggplot2)

# --- ЗАГРУЗКА ДАННЫХ ---
data <- read.csv("var_15.csv", sep = ";")
data_clean <- data[, !(names(data) %in% c("N"))]


# --- ПРИВЕДЕНИЕ ТИПОВ ---
# Преобразуем Group в фактор
data_clean$Group <- as.factor(data_clean$Group)
data_clean$Gender <- as.factor(data_clean$Gender)
data_clean$Activity.level..level. <- as.factor(data_clean$Activity.level..level.)

# Автоматически преобразуем строковые столбцы в факторы
for (col in names(data)) {
  if (is.character(data[[col]])) {
    data[[col]] <- as.factor(data[[col]])
  }
}

# --- ДЕЛЕНИЕ НА ГРУППЫ ---
data1 <- subset(data, Group == 1)  # Группа 1
data2 <- subset(data, Group == 2)  # Группа 2


# --- ВЫДЕЛЕНИЕ ЧИСЛОВЫХ ПРИЗНАКОВ ---
num1 <- data1[, sapply(data1, is.numeric)]  # Числовые признаки для группы 1
num2 <- data2[, sapply(data2, is.numeric)]  # Числовые признаки для группы 2
num_vars <- data_clean[, sapply(data_clean, is.numeric)]

# ===============================
# ПРОВЕРКА НОРМАЛЬНОСТИ РАСПРЕДЕЛЕНИЯ
# ===============================

# Функция для хи‑квадрат теста
chi_sq_test <- function(x) {
  x <- na.omit(x)
  bins <- cut(x, breaks = nclass.Sturges(x))
  observed <- table(bins)
  expected <- rep(length(x) / length(observed), length(observed))
  chisq.test(observed, p = expected / sum(expected))
}
cat("=== ПРОВЕРКА НОРМАЛЬНОСТИ — ГРУППА 1 ===\n")
for (col in names(num1)) {
  cat("Признак:", col, "\n")
  
  # Проверка на нулевое отклонение
  if (sd(num1[[col]], na.rm = TRUE) == 0) {
    cat("  ВНИМАНИЕ: Все значения одинаковы, тесты на нормальность не применимы\n")
    next
  }
  
  print(shapiro.test(num1[[col]]))
  print(ad.test(num1[[col]]))
  print(cvm.test(num1[[col]]))
  print(chi_sq_test(num1[[col]]))
}

cat("\n=== ПРОВЕРКА НОРМАЛЬНОСТИ — ГРУППА 2 ===\n")
for (col in names(num2)) {
  cat("Признак:", col, "\n")
  
  # Проверка на нулевое отклонение
  if (sd(num2[[col]], na.rm = TRUE) == 0) {
    cat("  ВНИМАНИЕ: Все значения одинаковы, тесты на нормальность не применимы\n")
    next
  }
  
  print(shapiro.test(num2[[col]]))
  print(ad.test(num2[[col]]))
  print(cvm.test(num2[[col]]))
  print(chi_sq_test(num2[[col]]))
}


# --- ПОСТРОЕНИЕ ГИСТОГРАММ ---
cat("\n=== ПОСТРОЕНИЕ ГИСТОГРАММ ===\n")
for (col in names(num1)) {
  par(mfrow = c(1, 2))  # Разбиваем окно на 2 графика
  hist(num1[[col]], probability=TRUE, main=paste("Group 1 -", col))
  lines(density(num1[[col]]), col="blue")
  
  hist(num2[[col]], probability=TRUE, main=paste("Group 2 -", col))
  lines(density(num2[[col]]), col="blue")
}

# ===============================
# РАСЧЁТ КОРРЕЛЯЦИЙ
# ===============================
cat("\n=== РАСЧЁТ КОРРЕЛЯЦИЙ ===\n")

# Пирсон
cor_pearson1 <- cor(num1, use = "pairwise.complete.obs")
cor_pearson2 <- cor(num2, use = "pairwise.complete.obs")

# Спирмен
cor_spear1 <- cor(num1, method = "spearman", use = "pairwise.complete.obs")
cor_spear2 <- cor(num2, method = "spearman", use = "pairwise.complete.obs")

# Кендалл
cor_kendall1 <- cor(num1, method = "kendall", use = "pairwise.complete.obs")
cor_kendall2 <- cor(num2, method = "kendall", use = "pairwise.complete.obs")

# Вывод результатов
print("Корреляция Пирсона — Группа 1:")
print(cor_pearson1)
print("Корреляция Пирсона — Группа 2:")
print(cor_pearson2)
print("Корреляция Спирмена — Группа 1:")
print(cor_spear1)
print("Корреляция Спирмена — Группа 2:")
print(cor_spear2)
print("Корреляция Кендалла — Группа 1:")
print(cor_kendall1)
print("Корреляция Кендалла — Группа 2:")
print(cor_kendall2)

# ===============================
# ПРОВЕРКА ЗНАЧИМОСТИ КОРРЕЛЯЦИИ
# ===============================
cat("\n=== ПРОВЕРКА ЗНАЧИМОСТИ КОРРЕЛЯЦИИ ===\n")
for (i in 1:(ncol(num1) - 1)) {
  for (j in (i + 1):ncol(num1)) {
    cat("Корреляция:", names(num1)[i], "—", names(num1)[j], "\n")
    print(cor.test(num1[[i]], num1[[j]]))
  }
}

# ===============================
# ЧАСТНАЯ КОРРЕЛЯЦИЯ
# ===============================
cat("\n=== ЧАСТНАЯ КОРРЕЛЯЦИЯ ===\n")
pcor1 <- pcor(num1)
pcor2 <- pcor(num2)

print("Частная корреляция — Группа 1 (оценки):")
print(pcor1$estimate)
print("Частная корреляция — Группа 1 (p‑значения):")
print(pcor1$p.value)

print("Частная корреляция — Группа 2 (оценки):")
print(pcor2$estimate)
print("Частная корреляция — Группа 2 (p‑значения):")
print(pcor2$p.value)

# ===============================
# ТЕПЛОВЫЕ КАРТЫ КОРРЕЛЯЦИЙ
# ===============================
cat("\n=== ТЕПЛОВЫЕ КАРТЫ КОРРЕЛЯЦИЙ ===\n")
corrplot(cor_pearson1, method = "color", type = "upper", title = "Группа 1 — Корреляция Пирсона")
corrplot(cor_pearson2, method = "color", type = "upper", title = "Группа 2 — Корреляция Пирсона")

# ===============================
# ANOVA И КРИТЕРИЙ КРАСКЕЛА — УОЛЛИСА
# ===============================
cat("\n=== ANOVA И КРИТЕРИЙ КРАСКЕЛА — УОЛЛИСА ===\n")
for (col in names(num1)) {
  cat("ANOVA для:", col, "\n")
  print(summary(aov(data[[col]] ~ data$Group)))
  
  cat("Критерий Краскела — Уоллиса для:", col, "\n")
  print(kruskal.test(data[[col]] ~ data$Group))
}

# ===============================
# ТАБЛИЦЫ СОПРЯЖЕННОСТИ И СТАТИСТИЧЕСКИЕ ТЕСТЫ
# ===============================
cat("\n=== ТАБЛИЦЫ СОПРЯЖЕННОСТИ ===\n")
factor_cols <- names(data)[sapply(data, is.factor)]

for (i in 1:(length(factor_cols) - 1)) {
  for (j in (i + 1):length(factor_cols)) {
    cat("Таблица сопряженности:", factor_cols[i], "—", factor_cols[j], "\n")
    tbl <- table(data[[factor_cols[i]]], data[[factor_cols[j]]])
    print("Хи‑квадрат тест:")
    print(chisq.test(tbl))
    print("Точный критерий Фишера:")
    print(fisher.test(tbl))
  }
}

# ===============================
# МАТРИЧНЫЙ ГРАФИК РАСПРЕДЕЛЕНИЙ
# ===============================
cat("\n=== МАТРИЧНЫЙ ГРАФИК ===\n")
library(GGally)

ggpairs(num_vars,
        aes(color = data_clean$Group, alpha = 0.5),
        upper = list(continuous = "cor"),
        lower = list(continuous = "smooth"),
        diag = list(continuous = "densityDiag"))