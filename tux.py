from PIL import Image

def rgbTOhex(rgb):
     return '%02x%02x%02x' % rgb

def solve(directory, maxNum):

     im = Image.open(directory)
     pix = im.load()
     print (" R    G    B      Hexa     LastChar    Binary      2ndBit    PixelNR")
     result = []

     for x in range(maxNum):

          color = pix[x,0]
          last = rgbTOhex(color)[5]
          b = ''.join(format(ord(i), '08b') for i in last)

          print (color,"  ", rgbTOhex(color), "     ", last, "     ", b, "     ", b[-3], "       ", x)
          result.append(b[-3])

     out = ""
     for bit in result:
          print(bit, end = "")
          out += bit

     print("\n")
     print(out, end = "\n")

if __name__ == "__main__":
     solve("tux.png", 100)