let data = new Set([1, 2, 2, 2, 3]);
console.log(data);

data.add("hello")
console.log(data)

data.delete(3)
console.log(data)

data.has(1)
console.log(data)

// data.clear()
// console.log(data)

console.log(data.keys())
console.log(data.entries())
console.log(data.values())