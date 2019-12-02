from PIL import Image

img = Image.open("MathPic.ppm")
img.save("a.bmp")
img.show()