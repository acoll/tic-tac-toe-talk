const boardEl = document.querySelector(".board");
const resetBtn = document.querySelector(".App-header button");
const cells = document.querySelectorAll(".cell");
const title = document.querySelector(".App-header h3");

let currentPlayer = "X";

const directions = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8],
  [0, 3, 6],
  [1, 4, 7],
  [2, 5, 8],
  [0, 4, 8],
  [2, 4, 6]
];

function getWinner(cells = []) {
  const rows = directions.map(dir => dir.map(index => cells[index]));

  const winningRow = rows.find(row => {
    const first = row[0].innerText;
    return first && row.every(node => node.innerText === first);
  });

  return winningRow && winningRow[0] && winningRow[0].innerText;
}

boardEl.addEventListener("click", event => {
  if (event.target.classList.contains("cell")) {
    event.target.innerText = currentPlayer;

    // toggle the player
    currentPlayer = currentPlayer === "X" ? "O" : "X";

    title.innerText = `${currentPlayer}'s Turn`;

    const winner = getWinner(cells);

    if (winner) {
      title.innerText = `${winner} Wins!`;
      title.classList.add("winning-title");
    }
  }
});

resetBtn.addEventListener("click", event => {
  cells.forEach(cell => (cell.innerText = ""));
});
