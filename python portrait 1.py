import PIL
from PIL import Image
from PIL import ImageEnhance
import serial
import time


ASCII_CHARS = [ '@', '%', '#', 'x', '+', '=', ';', ',', '-', '.', ' ']

def scale_image(image, new_width=65):
    """Resizes an image preserving the aspect ratio.
    """
    (original_width, original_height) = image.size
    aspect_ratio = original_height/float(1.63603*original_width)
    new_height = int(aspect_ratio * new_width)

    new_image = image.resize((new_width, new_height))
    return new_image

def convert_to_grayscale(image):
    return image.convert('L')

def increase_contrast(image):
    enhancer = ImageEnhance.Contrast(image)
    return  enhancer.enhance(1.7)

def map_pixels_to_ascii_chars(image, range_width=25):
    """Maps each pixel to an ascii char based on the range
    in which it lies.

    0-255 is divided into 11 ranges of 25 pixels each.
    """

    pixels_in_image = list(image.getdata())
    pixels_to_chars = [ASCII_CHARS[int(pixel_value/range_width)] for pixel_value in
            pixels_in_image]

    return "".join(pixels_to_chars)

def convert_image_to_ascii(image, new_width=65):
    image = scale_image(image)
    image = convert_to_grayscale(image)
    image = increase_contrast(image)

    pixels_to_chars = map_pixels_to_ascii_chars(image)
    len_pixels_to_chars = len(pixels_to_chars)

    image_ascii = [pixels_to_chars[index: index + new_width] for index in
            range(0, len_pixels_to_chars, new_width)]

    return image_ascii

def handle_image_conversion(image_filepath):
    image = None
    try:
        image = Image.open(image_filepath)
    except Exception as e:
##        print("Unable to open image file {image_filepath}.".format(image_filepath=image_filepath)
        print(e)
        return

    image_ascii = convert_image_to_ascii(image)
    print ("\n".join(image_ascii))
    return image_ascii



if __name__=='__main__':
    import sys

    image_file_path = sys.argv[1]
    image_ascii = handle_image_conversion(image_file_path)

## Serial print handling here
ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM7'
ser.setDTR(value=0)
ser.open()


for m in range(0,len(image_ascii)):
   ready_state = b'\0'
   
   line = image_ascii[m]
   line_to_send = line.encode('ascii')
   print(int((m/len(image_ascii))*100),"% complete")
   ser.write(line_to_send)
   ser.write(b'\n')
   while ready_state != b'R':
       ready_state = ser.read(size=1)

ser.close()


    
    



