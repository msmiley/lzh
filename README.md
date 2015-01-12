# lzh

Compression/Decompression using lzh/lzhuff

The Lempel-Ziv-Huffman algorithm was written by Haruyasu Yoshizaki 11/20/1988. It is relatively obscure but still shows up occasionally. This package currently only handles buffers with a 4-byte uncompressed-length header. The more complex headers which came later (LHA/LHarc) are not currently supported.

## Installation

```bash
$ npm install lzh
```

## Usage

```js
lzh = require('lzh')
lzh.decompress(new Buffer(...))
```

## Testing

```bash
$ npm test
```

## License

  [MIT](LICENSE)
