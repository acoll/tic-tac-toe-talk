export const directions = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8],
  [0, 3, 6],
  [1, 4, 7],
  [2, 5, 8],
  [0, 4, 8],
  [2, 4, 6]
];

export function detectWinner(cells = []) {
  const rows = directions.map(dir => dir.map(index => cells[index]));

  const winningRow = rows.find(row => {
    const first = row[0];
    return first !== null && row.every(index => index === first);
  });

  return winningRow;
}

export function detectCurrentPlayerTurn(cells = []) {
  const xCount = cells.filter(cell => cell === "X").length;
  const oCount = cells.filter(cell => cell === "O").length;

  console.log(xCount, oCount, xCount > oCount ? "O" : "X");

  return xCount > oCount ? "O" : "X";
}
