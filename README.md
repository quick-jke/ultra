# 🚀 Quick::Ultra ORM

**Quick::Ultra** — C++ ORM, позволяющая работать с реляционными базами данных через объектно-ориентированный интерфейс. На данный момент поддерживается **MySQL** с базовыми операциями: `SELECT`, `INSERT`, `UPDATE`, `CREATE TABLE`, `SAVE` и др.

> ⚠️ **Внимание:** Проект находится в активной разработке. API может меняться.

---

## 🔧 Возможности

- ✅ Подключение к MySQL через драйвер
- ✅ Автоматическое создание таблиц (`CREATE TABLE`)
- ✅ Поддержка связей "один к одному"
- ✅ CRUD операции: `get_by_id`, `get_all`, `save`, `execute`
- ✅ Поддержка кастомных Dialect'ов (на данный момент — `MySQLDialect`)
- ✅ Автоматическое управление зависимостями (сохранение связанных объектов)

---

## 📦 Установка

Проект написан на C++17 и требует:
- CMake (рекомендуется 3.14+)
- Компилятор с поддержкой C++17
- Библиотеку MySQL Connector/C++ (или совместимую)
```bash
sudo apt install libmysqlcppconn8-dev libmysqlclient-dev -y
```
или
```bash
sudo apt install libmysqlcppconn-dev libmysqlclient-dev -y
```


### Сборка

```bash
git clone https://github.com/quick-jke/ultra.git
cd ultra
mkdir build && cd build
cmake ..
make
```
