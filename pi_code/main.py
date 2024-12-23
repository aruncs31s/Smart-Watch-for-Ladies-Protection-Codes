"""
 Source: https://www.geeksforgeeks.org/python-convert-speech-to-text-and-text-to-speech/
"""

import pyttsx3
import speech_recognition as sr

r = sr.Recognizer()


def SpeakText(command):

    engine = pyttsx3.init()
    engine.say(command)
    engine.runAndWait()


while 1:
    try:

        # use the microphone as source for input.
        with sr.Microphone() as source2:
            r.adjust_for_ambient_noise(source2, duration=0.2)

            audio2 = r.listen(source2)

            MyText = r.recognize_google(audio2)
            MyText = MyText.lower()
            print("Text", MyText)
            # SpeakText(MyText)
    except sr.RequestError as e:
        print("Could not request results; {0}".format(e))

    except sr.UnknownValueError:
        print("unknown error occurred")
