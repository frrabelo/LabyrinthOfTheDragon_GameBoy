const fs = require('fs');
const { PNG } = require('pngjs');

const ColorMap = {
  '#000000': 0,
  '#555555': 1,
  '#ACACAC': 2,
  '#FFFFFF': 3
}

function rgbToHex (r, g, b) {
  return '#' + [r, g, b].map(v => {
    let hex = v.toString(16).toUpperCase()
    return hex.length < 2 ? `0${hex}` : hex;
  }).join('')
}

function mapColor(r, g, b) {
  const hex = rgbToHex(r, g, b)
  switch (hex) {
  case '#000000': return 0;
  case '#555555': return 1;
  case '#ACACAC': return 2;
  case '#FFFFFF': return 3
  }
  throw new Error(`Encountered Invalid Color: ${hex}`)
}

function getTileBytes(image, tx, ty) {
  // Map the image's colors to 2bpp values and arrange the tile in a 2d array
  const tile = [];
  for (let y = 0; y < 8; y++) {
    tile.push([])
    for (let x = 0; x < 8; x++) {
      const idx = ((ty * 8 + y) * image.width + (tx * 8 + x)) * 4;
      const r = image.data[idx];
      const g = image.data[idx + 1];
      const b = image.data[idx + 2];
      tile[tile.length - 1].push(mapColor(r, g, b))
    }
  }

  // Convert the 2d array to GB 2BPP binary
  const bytes = []
  tile.forEach(row => {
    let low = 0;
    let high = 0;
    row.forEach(c => {
      low = (low << 1) | (c & 1)
      hight = (high << 1) | (c >> 1)
    })
    bytes.push(low)
    bytes.push(high)
  })

  return bytes
}

function parseImage () {
  console.log(`Image width: ${this.width}`);
  console.log(`Image height: ${this.height}`);
  console.log(`Total pixels: ${this.width * this.height}`);

  if (this.width % 8 !== 0) {
    throw new Error(`Image width (${this.width}) is not a multiple of 8.`)
  }

  if (this.height % 8 !== 0) {
    throw new Error(`Image height (${this.height}) is not a multiple of 8`)
  }

  const tileWidth = this.width / 8;
  const tileHeight = this.height / 8;
  const bytes = []

  for (let ty = 0; ty < tileHeight; ty++)
  for (let tx = 0; tx < tileWidth; tx++) {
    getTileBytes(this, tx, ty).forEach(b => bytes.push(b))
  }

  fs.writeFileSync('./output.bin', new Uint8Array(bytes));
}

const filePath = '../assets/font.png';

fs.createReadStream(filePath)
  .pipe(new PNG())
  .on('parsed', parseImage)
  .on('error', (err) => {
    console.error(`Error reading the PNG file: ${err.message}`);
  });
