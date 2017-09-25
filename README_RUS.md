# SpeechRecognizer
Проект офлайн распознавания речи. В основе - pocketsphinx(статическая сборка).
---------
Основа проекта - динамическая библиотека SpeechRecognizer (SpeechRecognizer->lib->dynamic).

Приложение для демонстрации работы по распознаванию речи - VoiceRecognition (SpeechRecognizer->app).

Сборка проводилась на Windows 10 x64, Qt 5.8 MSVC 2015

Для сборки необходимо собрать "головной" проект SpeechRecognizer. 

Для запуска приложения VoiceRecognition с демонстрацией работы распознавания речи необходимо:
1. В папку с исполняемым файлом извлечь акустические модели для разных языком из архива https://cloud.mail.ru/public/74Jz/ifWwr2p2r
2. В папку с исполняемым файлом скопировать библиотеку SpeechRecognizer
3. Скопировать библиотеки Qt5Core.dll, Qt5Gui.dll, Qt5Widgets.dll в директорию с приложением VoiceRecognition
