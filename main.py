import speech_recognition as sr

# Initialize recognizer class (for recognizing the speech)
r = sr.Recognizer()

# Reading Microphone as source
# listening the speech and store in audio_text variable
with sr.Microphone() as source:

    while True:
        audio_text = r.listen(source)
        try:
            # using google speech recognition
            print("Text: " + r.recognize_google(audio_text))
        except:
            print("Unable to hear")

"
