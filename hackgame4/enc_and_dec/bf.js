/* author: @ustc_zzzz */ class BF {
  constructor (write, read) {
    this.write = write || (o => 0 * setTimeout(console.log, 0, o) || (i => o.push(i)))([])
    this.read = read || (() => 0)
    this.pointer = 0
    this.data = []
    this.ops = {
      '>': (pointer, _) => {
          //指针加一
        ++this.pointer
        return pointer
      },
      '<': (pointer, _) => {
          //指正减一
        --this.pointer
        return pointer
      },
      ',': (pointer, _) => {
          //读取，如果没有read就补零
        this.data[this.pointer] = this.read()
        return pointer
      },
      '.': (pointer, _) => {
          //对这个数据取256的模
        let normalize = i => i < 0 ? i % 256 + 256 : i % 256
        this.write(normalize(this.data[this.pointer] || 0))
        return pointer
      },
      '+': (pointer, _) => {
          //data这个地方的数据加一
        this.data[this.pointer] = (this.data[this.pointer] || 0) + 1
        return pointer
      },
      '-': (pointer, _) => {
          //data这个地方的数据减一
        this.data[this.pointer] = (this.data[this.pointer] || 0) - 1
        return pointer
      },
      ']': (pointer, text) => {
        if ((this.data[this.pointer] || 0) % 256 === 0) return pointer
        for (let stack = 0; pointer >= 0; --pointer) {
          let char = text[pointer]
          if (char === '[') --stack
          if (char === ']') ++stack
          if (stack === 0) return pointer
        }
        throw new Error('Mismatched brackets in the program!')
      },
      '[': (pointer, text) => {
        if ((this.data[this.pointer] || 0) % 256 !== 0) return pointer
        for (let stack = 0; pointer < text.length; ++pointer) {
          let char = text[pointer]
          if (char === '[') ++stack
          if (char === ']') --stack
          if (stack === 0) return pointer
        }
        throw new Error('Mismatched brackets in the program!')
      }
    }
  }

  run (text) {
    for (let pointer = 0; pointer < text.length; ++pointer) {
      let op = this.ops[text[pointer]]
      pointer = op ? op(pointer, text) : pointer
    }
    return this
  }
}
