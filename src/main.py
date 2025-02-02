import speech_recognition as sr

import check_help

r = sr.Recognizer()

with sr.Microphone() as source:

    while True:
        audio = r.listen(source)
        audio_text = r.recognize_google(audio)
        try:
            check_help.detect_help("audio_text") and print("hi")

            print("Text: " + audio_text)
        except:
            print("Unable to hear")
