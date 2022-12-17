from PIL import Image
import requests

# This function will pass your text to the machine learning model
# and return the top result with the highest confidence
def classify(text):
    key = "f20bfe20-7e02-11ed-9171-c3d870b2dd9ecdb970b0-5803-4031-a81f-d005b24a7457"
    url = "https://machinelearningforkids.co.uk/api/scratch/"+ key + "/classify"

    response = requests.get(url, params={ "data" : text })

    if response.ok:
        responseData = response.json()
        topMatch = responseData[0]
        return topMatch
    else:
        response.raise_for_status()

input = input("What do you want to tell me? > ")
recognized = classify(input)
label = recognized["class_name"]

if label == "good_things":
     print ("You're so nice!")
     #img = Image.open('happy.png')
     #img.show()
else:
     print ("You're so mean!")
     #img = Image.open('sad.png')
     #img.show()
