Project of off-line speech recognizing. On the basis of library pocketsphinx (static assembly).
---------
The basis of the project is dynamic library SpeechRecognizer (SpeechRecognizer->lib->dynamic).

Library SpeechRecognizer has been created for future integration to the projects on Unity 5 by means of using wrapper (connector) UnitySpeechRecognizer (https://github.com/MimusTriurus/UnitySpeechRecognizer ).

Application for demonstration of speech recognizing:  VoiceRecognition (SpeechRecognizer->app).

System requirements:
---------
1. ОС: Windows(x86, x64), Ubuntu 16.04(x86, x64), Raspbian;
2. Qt 5.5.1 or higher;
3. Compiler with support for c++ 11;
4. Microphone.

Setup for Windows:
---------
1. Clone the repository;
2. If required – setup compilation flag –  j*, where “*” is the number of cores being used in the process of compilation;
3. Build main project SpeechRecognizer;
4. Download files of acoustic model  https://cloud.mail.ru/public/74Jz/ifWwr2p2r and expand compressed files to the folder with  executive file VoiceRecognition.exe.

Setup for Linux:
---------
1. Clone the repository;
2. Install library libasound2-dev by keying in in the console command “sudo apt-get install libasound2-dev” (so that pocketsphinx used Alsa, not pulseaudio by default);
3. If required – setup compilation flag –  j*, where “*” is the number of cores being used in the process of compilation;
4. Build main project SpeechRecognizer;
5. Download files of acoustic model  https://cloud.mail.ru/public/74Jz/ifWwr2p2r and expand compressed files to the folder with  executive file VoiceRecognition.

Setup for  Raspbian:
---------
1. Create swap file (size 1 Gb) following the steps as below:
	a) open the file by keying in in the console command “sudo nano /etc/dphys-swapfile”;
	b) change the value CONF_SWAPSIZE to 1024;
	c) save the file by pressing [Ctrl+O], then press [Enter] to confirm and press [Ctrl+X].
2. Clone the repository;
3. Install library libasound2-dev by keying in in the console command “sudo apt-get install libasound2-dev” (so that pocketsphinx used Alsa, not pulseaudio by default);
4. If required – setup compilation flag –  j*, where “*” is the number of cores being used in the process of compilation;
5. Build main project SpeechRecognizer;
6. Download files of acoustic model  https://cloud.mail.ru/public/74Jz/ifWwr2p2r and expand compressed files to the folder with  executive file VoiceRecognition.

Remarks:
---------
1. For static assembly of libraries pocketsphinx command “make” is to be executed with flag CFLAGS="-static";
2. For setup of compiled libraries it is required to execute command in the console “make install DESTDIR=<catalogue>”;
3. Test application VoiceRecognition and library SpeechRecognizer are located in folder “bin”;
4. So that application VoiceRecognition could work with a certain microphone it is required to start the program  with parameter "-adcdev hw:0,0" ( where hw:0,0 – identifier of the microphone. For example, “hw:1,0” for microphone of  usb web-camera on raspberry ), otherwise default  device will be used;
5. To improve the quality of recognition it is required to tune the microphone in such a way, so that it sensed as little back-ground noise as possible.
