import serial
import barcode
from barcode.writer import ImageWriter
import os
import win32print  # For Windows printing

# Open the serial connection to the Arduino
arduino = serial.Serial('COM3', 9600, timeout=1)

def generate_and_print_barcode(barcode_data):
    try:
        # Generate a barcode image (Code 128 format)
        barcode_format = barcode.get_barcode_class('code128')
        barcode_image = barcode_format(barcode_data, writer=ImageWriter())

        # Save the barcode image to a temporary file
        temp_file = "temp_barcode"
        barcode_image.save(temp_file)
        barcode_file = f"{temp_file}.png"

        # Print the barcode using the default printer
        printer_name = win32print.GetDefaultPrinter()
        print(f"Printing to: {printer_name}")

        printer_handle = win32print.OpenPrinter(printer_name)
        job_id = win32print.StartDocPrinter(printer_handle, 1, ("Barcode Print Job", None, "RAW"))
        win32print.StartPagePrinter(printer_handle)

        with open(barcode_file, "rb") as f:
            raw_data = f.read()
            win32print.WritePrinter(printer_handle, raw_data)

        win32print.EndPagePrinter(printer_handle)
        win32print.EndDocPrinter(printer_handle)
        win32print.ClosePrinter(printer_handle)

        print("Barcode printed successfully!")
    except Exception as e:
        print(f"Error printing barcode: {e}")
    finally:
        # Clean up the temporary file
        if os.path.exists(barcode_file):
            os.remove(barcode_file)

def main():
    while True:
        try:
            # Check for incoming data from the Arduino
            if arduino.in_waiting > 0:
                barcode_data = arduino.readline().decode('utf-8').strip()

                if barcode_data:
                    print(f"Received barcode data: {barcode_data}")

                    # Generate and print the barcode
                    generate_and_print_barcode(barcode_data)
        except KeyboardInterrupt:
            print("Exiting...")
            break
        except Exception as e:
            print(f"Error: {e}")

if __name__ == "__main__":
    try:
        main()
    finally:
        arduino.close()
