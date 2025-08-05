## Part 1. Настройка gitlab-runner

### Скачать и установить на виртуальную машину gitlab-runner

![](/misc/1.1%20Ubuntu%2022.png)

1.Загрузить бинарный файл 

```sh
sudo curl -L --output /usr/local/bin/gitlab-runner "https://s3.dualstack.us-east-1.amazonaws.com/gitlab-runner-downloads/latest/binaries/gitlab-runner-linux-amd64"
```

2.Дать файлу разрешение на исполнение

```sh
sudo chmod +x /usr/local/bin/gitlab-runner
```
3 Создать пользователя GitLab CI
```sh
sudo useradd --comment 'GitLab Runner' --create-home gitlab-runner --shell /bin/bash
```

4.Установить как службу
```sh
sudo gitlab-runner install --user=gitlab-runner --working-directory=/home/gitlab-runner
```
5.Запустить службу

sudo gitlab-runner start

![](/misc/1.2%20sudo%20gitlab-runner%20start.png)

### Запустить gitlab-runner и зарегистрировать его для использования в текущем проекте (DO6_CICD)

`Переходим на страницу задания и получаем токен`
![](/misc/1.3%20Token.png)

```sh
sudo gitlab-runner register
```
Зарегистрировать gitlab-runner

Для этого необходимо ввести данные при регистрации:

Cвой URL-адрес GitLab
Cвой регистрационный токен
Название раннера
Теги для заданий, разделенные запятыми
Тип исполнителя

![](/misc/1.4%20sudo%20gitlab-runner%20register.png)

## Part 2. Сборка
### Напиcать этап для CI по сборке приложений из проекта C2_SimpleBashUtils

`В корне репозитория создать файл .gitlab-ci.yml`

![](/misc/2.1%20.gitlab-ci.png)

![](/misc/2.1%202.png)

![](/misc/2.1%203%20qwe.png)

При пуше я столкнулся со следующей ошибкой:

![](/misc/2.2%20%20Makefile%20.png)

Устанаовка Make в Ubuntu 
`sudo apt update`
`sudo apt install make`

При пуше я столкнулся со следующей ошибкой:

![](/misc/2.2%20pcre.png)

Установка библиотеки:
`sudo apt update`
`sudo apt install libpcre3 libpcre3-dev`

При следующем пуше ошибке не было

![](/misc/2.4%20stage_build.png)

![](/misc/2.3%20passed.png)

## Part 3. Тест кодстайла

### Напиcать этап для CI, который запускает скрипт кодстайла (clang-format)

![](/misc/3.1%20.png)

Проверим сначала вывод команды локально

![](/misc/3.2%201.png)
![](/misc/3.2%202.png)

Вывод пайплайна совпал с локальным выводом команды

![](/misc/3.4%20failed%20.png)

![](/misc/3.3%20failed.png)

Исправим ошибку 

![](/misc/3.4%20passed.png)

![](/misc/3.3%20passed.png)

## Part 4. Интеграционные тесты

### Написать этап для CI, который запускает интеграционные тесты из того же проекта

![](/misc/4.1.png)

![](/misc/4.2%20.png)

![](/misc/4.3.png)

Добавить права на выполнение для test.sh

`chmod +x src/grep/test.sh`

`git add src/grep/test.sh`
`git commit -m Add execute permissions for test.sh`
`git push`

![](/misc/4.4.png)
![](/misc/4.5.png)
![](/misc/4.6.png)

### Part 5. Этап деплоя

- На ws1 где запущен runner сменить пользователя `sudo su gitlab-runner`
- Сгенерировать `ключ ssh-keygen -t rsa -b 2048`
- Добавил его в файл `/.ssh/authorized_keys`командой ssh-copy-id ellensem@192.10.10.1

Написал этап для CD, который «разворачивает» проект на другой виртуальной машине:

![](/misc/5.1.png)

![](/misc/5.2.png)

![](/misc/5.3.png)










