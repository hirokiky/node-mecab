const { Tagger } = require('./build/Release/mecab.node')

const tagger = new Tagger()
console.log(tagger.parse("Taggerを作って文字列も渡せるよ。NodeからC++のMeCabを呼ぶよ。gypやったね"))
