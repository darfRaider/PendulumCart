import numpy as np
from reportlab.pdfgen.canvas import Canvas
from PIL import Image
from reportlab.lib.units import cm 
import sys
import math
import qrcode
from pyzbar.pyzbar import decode
import cv2
import qrtools
FILENAME = "genCode"
EXT = "png"
A4 = [21*cm, 29.7*cm]

canvas = Canvas("hello.pdf")

N_characters_per_code = 128
qr = qrcode.QRCode(
    version=1,
    error_correction=qrcode.constants.ERROR_CORRECT_H,
    box_size=20,
    border=4,
)

f = open(sys.argv[1],"rb")
lines = f.readlines()
f.close()
images = []
def generateCode(text, filename):
    qr.clear()
    qr.add_data(text)
    qr.make(fit=True)
    img = qr.make_image(fill_color="black", back_color="white")
    images.append(img)
    img.save(filename)
    print("Generated code " + filename)

nCharacters = 0;
nCode = 0;
text = "";
isFull = False;

partitions = [];

for i, l in enumerate(lines):
    charsPerLine = 0;
    for c in l:
        charsPerLine += 1
    if nCharacters + charsPerLine > N_characters_per_code:
        partitions.append(i-1)
        nCharacters = charsPerLine;
    else:
        nCharacters += charsPerLine

partitions.append(len(lines)-1)

print("Generating " + str(len(partitions)) + " partitions...")

part = 0
for i, l in enumerate(lines):
    if i <= partitions[part]:
        text += str(l);
    if i == partitions[part]:
        fName = FILENAME+str(part)+"."+EXT 
        text = "-- PAGE " + str(part+1) + " --\n" + text 
        generateCode(text, fName)
        part += 1
        text = ""
        isFull = False
img2 = cv2.imread(FILENAME+str(0)+"."+EXT)
img = cv2.imread(FILENAME+str(0)+"."+EXT)
img = np.vstack((img,img, img, img, img, img))
cv2.imwrite("lol.png", img)
detector = cv2.QRCodeDetector();
#data, bbox, straight_qrcode = detector.detectAndDecode(img)
#data = decode(img)

PatchSize = 5*cm
spacing = 1*cm
i = 2;
A = 3;
hspace = (A4[0]-A*PatchSize)/(A+1);

B = 5;
vspace = (A4[1]-B*PatchSize)/(B+1);
#img2 = Image.fromarray(images[2], 'RGB')
#canvas.drawInlineImage("genCode0.png", spacing, A4[1]-spacing-PatchSize, PatchSize, PatchSize)

for i, img in enumerate(images):
    j = math.floor((i/A)%(B))+1 
    k = i%A
    p = math.floor(i/A/B)
    if i != 0 and i%(A*B) == 0:
        canvas.showPage()
    print("Page = "+str(p)+", j = "+str(j)+", K = " + str(k))
    canvas.drawInlineImage(img, hspace+(hspace+PatchSize)*k, A4[1]-(vspace+PatchSize)*j, PatchSize, PatchSize)
canvas.save()
