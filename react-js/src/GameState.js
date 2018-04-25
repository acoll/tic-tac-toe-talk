import React from "react";
import { detectCurrentPlayerTurn, detectWinner } from "./util";

const buildInitialCells = () => new Array(9).fill(null);

export default class GameState extends React.Component {
  state = {
    cells: buildInitialCells()
  };
  placeMarker = index => () => {
    if (detectWinner(this.state.cells)) {
      return;
    }
    this.setState(state => {
      state.cells[index] = detectCurrentPlayerTurn(state.cells);
      return {
        ...state,
        cells: [...state.cells]
      };
    });
  };
  resetGameState = () =>
    this.setState({
      cells: buildInitialCells()
    });
  render() {
    const render = this.props.render || this.props.children;
    const { placeMarker, state, resetGameState } = this;
    return render({ state, placeMarker, resetGameState });
  }
}
