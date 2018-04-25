import React from "react";

export default function Board({
  cells = [null, null, null, null, null, null, null, null, null],
  placeMarker = () => {}
}) {
  return (
    <div className="board">
      {cells.map((cell, index) => (
        <div
          onClick={cell ? null : placeMarker(index)}
          key={index}
          className="cell"
        >
          {cell}
        </div>
      ))}
    </div>
  );
}
