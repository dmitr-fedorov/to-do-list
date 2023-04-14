# Список задач

Репозиторий содержит консольное приложение, которое представляет из себя список задач.  
Каждая задача содержит поля:
- Название
- Описание
- Дата
- Категория
- Статус

Задачи хранятся в файле tasks.txt в папке с приложением.  
После запуска программа считывает задачи из файла в список, который можно редактировать.  
В случае неудачи при считывании, выводится сообщение о том, что пошло не так, и программа продолжает работу с пустым списком.

## Команды
- ### add {name} {description} {date} {category}
Добавить новую задачу с переданными в аргументах полями.  
Аргумент, состоящий из нескольких слов, должнен заключаться в кавычки.  
Пример использования:
```
add "Go to work" "My job is amazing, I love it" "2022-12-28 10:00" "Routine"
```
- ### update {name}
Обновить задачу с именем *name*. Новые значения полей вводятся интерактивно друг за другом после ввода этой команды.

- ### done {name}
Отметить задачу с именем *name* как выполненную.

- ### delete {name}
Удалить задачу с именем *name*.

- ### save
Сохранить все изменения в файл.

- ### select *
Отобразить все задачи.

- ### select * where {predicate}
Отобразить задачи, которые подходят под критерии из *predicate*.  
*predicate* должен состоять из выражений, описывающих условие отбора задач: {имя поля} {оператор} {значение}.  
Комбинация выражений возможна с помощью слова *and*.  
Доступные операторы: like, <, <=, =, >=, >.  
Оператор *like* ищет задачи с полями, которые содержат подстроку, которая идет после этого оператора.  
Примеры использования команды:
```
select * where name="Go to work"
```
```
select * where description like "amazing"
```
```
select * where name like "work" and date >= "2020-01-05 12:15"
```