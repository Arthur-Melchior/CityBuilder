import os
import math
import re
from pathlib import Path

try:
    from PIL import Image
except ImportError:
    print("Pillow n'est pas installé.")
    print("Installe-le avec :")
    print("python -m pip install pillow")
    exit()

# =========================
# CONFIG
# =========================
INPUT_DIR = "raw_tiles"
OUTPUT_DIR = "tile_sheets"

TILE_SIZE = 512

BACKGROUND_COLOR = (0, 0, 0, 0)

SUPPORTED_EXTENSIONS = {
    ".png",
    ".jpg",
    ".jpeg",
    ".webp",
    ".bmp",
    ".tiff"
}

# =========================
# SNAKE CASE
# =========================
def to_snake_case(text):

    text = text.strip()

    text = re.sub(r"[^\w\s-]", "", text)

    text = re.sub(r"([a-z0-9])([A-Z])", r"\1_\2", text)

    text = re.sub(r"[\s\-]+", "_", text)

    text = re.sub(r"_+", "_", text)

    return text.lower().strip("_")

# =========================
# IMAGE FIT
# =========================
def fit_image_no_stretch(img):

    w, h = img.size

    ratio = min(TILE_SIZE / w, TILE_SIZE / h)

    new_w = int(w * ratio)
    new_h = int(h * ratio)

    img = img.resize(
        (new_w, new_h),
        Image.Resampling.LANCZOS
    )

    canvas = Image.new(
        "RGBA",
        (TILE_SIZE, TILE_SIZE),
        BACKGROUND_COLOR
    )

    x = (TILE_SIZE - new_w) // 2
    y = (TILE_SIZE - new_h) // 2

    canvas.paste(img, (x, y))

    return canvas

# =========================
# LOAD IMAGES
# =========================
def load_images(folder):

    images = []

    for file in sorted(os.listdir(folder)):

        ext = Path(file).suffix.lower()

        if ext not in SUPPORTED_EXTENSIONS:
            continue

        path = os.path.join(folder, file)

        try:
            img = Image.open(path).convert("RGBA")

            img = fit_image_no_stretch(img)

            # NOM DU FICHIER EN SNAKE_CASE
            filename = Path(file).stem
            filename = to_snake_case(filename)

            images.append((filename, img))

            print(f"OK : {file}")

        except Exception as e:
            print(f"SKIP : {path}")
            print(e)

    return images

# =========================
# TILE SHEET
# =========================
def create_tilesheet(images, output_path):

    if not images:
        return

    count = len(images)

    cols = math.ceil(math.sqrt(count))
    rows = math.ceil(count / cols)

    sheet = Image.new(
        "RGBA",
        (
            cols * TILE_SIZE,
            rows * TILE_SIZE
        ),
        BACKGROUND_COLOR
    )

    for i, (_, img) in enumerate(images):

        x = (i % cols) * TILE_SIZE
        y = (i // cols) * TILE_SIZE

        # AUCUN ESPACE ENTRE LES TUILES
        sheet.paste(img, (x, y), img)

    os.makedirs(
        os.path.dirname(output_path),
        exist_ok=True
    )

    sheet.save(output_path)

# =========================
# PROCESS
# =========================
def process_folders(input_dir, output_dir):

    for root, _, _ in os.walk(input_dir):

        images = load_images(root)

        if not images:
            continue

        # COMPOSE LE NOM AVEC LE CHEMIN
        relative = os.path.relpath(root, input_dir)

        parts = Path(relative).parts

        snake_parts = [
            to_snake_case(part)
            for part in parts
        ]

        composed_name = "_".join(snake_parts)

        output_path = os.path.join(
            output_dir,
            composed_name + ".png"
        )

        create_tilesheet(images, output_path)

        print("\n=========================")
        print(f"TILESHEET OK : {output_path}")
        print("=========================")

# =========================
# MAIN
# =========================
if __name__ == "__main__":

    process_folders(
        INPUT_DIR,
        OUTPUT_DIR
    )

    print("\nTerminé.")