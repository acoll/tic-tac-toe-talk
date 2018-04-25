import React from "react";
import { detectCurrentPlayerTurn, detectWinner } from "./util";

export default function GameSummary({ cells = [] }) {
  const row = detectWinner(cells);

  if (row) {
    return <h1 className="winning-title">{row[0]} Wins!</h1>;
  }

  const currentPlayerTurn = detectCurrentPlayerTurn(cells);

  return <h3>{`${currentPlayerTurn}'s Turn`}</h3>;
}
