const { PassThrough } = require('stream')
const fs = require('fs')

module.exports = class EdxIo {
	constructor () {
		this._writeStream = new PassThrough()
		this._fsWriteStream = fs.createWriteStream('./output.txt')
		this._writeStream.pipe(this._fsWriteStream)

		this._inputChunkSize = 32768
		this._input = fs.openSync('./input.txt', 'r')
		this._inputBuffer = Buffer.alloc(this._inputChunkSize)
		this._inputBufferOffset = this._inputChunkSize
		this._inputOffset = 0

		this._readBytes = []
		this.emptyChars = new Map().set(32, true).set(13, true).set(10, true)
	}

	write (value = '') {
		this._writeStream.push(value.toString())
	}
	
	writeLn (value = '') {
		this._writeStream.push(value.toString() + '\n')
	}

	nextInt () {
		const token = this.nextToken()
		return parseInt(token, 10)
	}

	nextFloat () {
		return parseFloat(this.nextToken())
	}

	nextToken () {
		let char = this._readChar()
		let added = 0
		while (char) {
			if (this.emptyChars.has(char) && added > 0) {
				break
			} else {
				this._readBytes[added++] = char
			}
			
			char = this._readChar()
		}

		return (added > 0)
			? String.fromCharCode.apply(String, this._readBytes.slice(0, added))
			: undefined
	}

	nextChar () {
		let char = this._readChar()
		while (char) {
			if (!this.emptyChars.has(char)) {
				return char
			}

			char = this._readChar()
		}
	}

	close () {
		this._writeStream.push(null)
		this._fsWriteStream.close()

		return new Promise((resolve, reject) => this._fsWriteStream.once('close', resolve).once('error', reject))
	}

	_readChar () {
		if (this._inputBufferOffset >= this._inputChunkSize) {
			fs.readSync(this._input, this._inputBuffer, 0, this._inputChunkSize, this._inputOffset)
			this._inputOffset += this._inputChunkSize
			this._inputBufferOffset = 0
		}

		return this._inputBuffer[this._inputBufferOffset++]
	}
}
