import qrcode
# Your URL here
query = "ASD=1000&"

url = "https://anthonyx4.github.io/qrCodeTesting/?" + query + query + query + query + query + query + query + query + query + query;
# Generate QR code

qr = qrcode.QRCode(
    version=1,
    box_size=2,  # Smaller box size = lower image resolution
    border=2
)
qr.add_data(url)
qr.make(fit=True)
img = qr.make_image()
img.save("small_qrcode.png")


# qr = qrcode.make(url)
# # Save to file
# qr.save("url_qrcode.png")