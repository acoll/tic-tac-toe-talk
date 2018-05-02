import { detectWinner, detectCurrentPlayerTurn } from "./util.js";

const boardEl = document.querySelector(".board");
const resetBtn = document.querySelector(".App-header button");
const cells = document.querySelectorAll(".cell");
const title = document.querySelector(".App-header h3");

boardEl.addEventListener("click", event => {
  if (event.target.classList.contains("cell") && !detectWinner(cells)) {
    const currentPlayer = detectCurrentPlayerTurn(cells);
    event.target.innerText = currentPlayer;

    title.innerText = `${detectCurrentPlayerTurn(cells)}'s Turn`;

    const winningRow = detectWinner(cells);

    if (winningRow) {
      title.innerText = `${winningRow[0].innerText} Wins!`;
      title.classList.add("winning-title");
    }
  }
});

resetBtn.addEventListener("click", event => {
  cells.forEach(cell => (cell.innerText = ""));
});
