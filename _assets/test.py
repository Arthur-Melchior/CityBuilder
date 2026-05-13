import os
import math
from PIL import Image

# =========================
# CONFIGURATION
# =========================
INPUT_DIR = "CityBuilder Assets"
OUTPUT_DIR = "output_sheets"
TILE_SIZE = (512, 512)
BACKGROUND_COLOR = (0, 0, 0, 0)  # transparent (RGBA)

# =========================
# FIT SANS DEFORMATION
# =========================
def fit_image(img, size):
    img.thumbnail(size, Image.Resampling.LANCZOS)

    canvas = Image.new("RGBA", size, BACKGROUND_COLOR)

    x = (size[0] - img.width) // 2
    y = (size[1] - img.height) // 2

    canvas.paste(img, (x, y))
    return canvas

# =========================
# CHARGER IMAGES
# =========================
def load_images(folder):
    images = []

    for file in sorted(os.listdir(folder)):
        if file.lower().endswith((".png", ".jpg", ".jpeg", ".webp", ".bmp", ".tiff")):
            path = os.path.join(folder, file)

            try:
                img = Image.open(path).convert("RGBA")
                img = fit_image(img, TILE_SIZE)
                images.append(img)
            except:
                print(f"Skip: {path}")

    return images

# =========================
# CREER TILE SHEET
# =========================
def create_tilesheet(images, output_path):
    if not images:
        return

    cols = math.ceil(math.sqrt(len(images)))
    rows = math.ceil(len(images) / cols)

    sheet = Image.new("RGBA", (cols * TILE_SIZE[0], rows * TILE_SIZE[1]), BACKGROUND_COLOR)

    for i, img in enumerate(images):
        x = (i % cols) * TILE_SIZE[0]
        y = (i // cols) * TILE_SIZE[1]
        sheet.paste(img, (x, y), img)

    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    sheet.save(output_path)

# =========================
# PARCOURS RECURSIF
# =========================
def process_folders(input_dir, output_dir):
    for root, _, _ in os.walk(input_dir):
        images = load_images(root)

        if images:
            rel_path = os.path.relpath(root, input_dir)
            output_path = os.path.join(output_dir, rel_path + ".png")

            create_tilesheet(images, output_path)
            print(f"Tilesheet OK : {output_path}")

# =========================
# RUN
# =========================
if __name__ == "__main__":
    process_folders(INPUT_DIR, OUTPUT_DIR)
    print("Terminé.")