#include <QCoreApplication>
#include <QAudioRecorder>
#include <QDebug>

int main( int argc, char *argv[ ] )
{
    QCoreApplication a( argc, argv );

    QAudioRecorder *audioRecorder = new QAudioRecorder;

    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/amr");
    audioSettings.setQuality(QMultimedia::HighQuality);

    audioRecorder->setEncodingSettings(audioSettings);
    qDebug( ) << "default:" << audioRecorder->defaultAudioInput( );
    qDebug( ) << "inputs=:" << audioRecorder->audioInputs( );

    return a.exec( );
}

