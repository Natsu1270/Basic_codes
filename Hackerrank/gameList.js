function howManyGames2(p,d,m,s) {
    let count = 0
    s = s - p
    while (s>=0) {
        count += 1
        const pd = p - d >= m ? p - d : m 
        s = s - pd
    }
    return count
}

function howManyGames(p, d, m, s) {
    // Return the number of games you can buy
    // 20 3 6 80
    let res = 0;
    const buyList = []
    buyList.push(p)
    let pd = p - d 
    while (pd > m) {
        buyList.push(pd)
        pd = pd - d 
    }

    buyList.forEach(game => {
        s -= game
        if (s >= 0) {
            res += 1
        }
    })
    if (s > 0) res += Math.floor(s/m)
    
    return res
    
}

console.log(howManyGames2(100, 19, 1, 180))