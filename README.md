# AlgoVisual

Algorithm Visualizer - Interactive Learning Platform

A JavaScript/CSS/HTML application for visualizing key algorithms with graphics and smooth UI transitions.

## Features

- Landing page with hero animation and algorithm bar visualization.
- Algorithms section: Dijkstra, Bubble Sort, Selection Sort, Insertion Sort.
- Team cards with consistent social links and responsive layout.
- Node.js backend endpoint for running algorithms.

## Structure

- `public/`
  - `index.html` – main UI markup.
  - `styles.css` – visual styling, animations, responsive grid.
  - `img/` – team avatar images, icons.
- `server/`
  - `server.js` – Express-based API to run algorithm logic.
- `native/src/` – C++ source codes for algorithm implementations (bubble, insertion, selection, Dijestra).
- `package.json` – project metadata and dependencies.

## Getting Started

### Prerequisites

- Node.js (>=16)
- npm

### Run Locally

1. Clone the repository:
   ```bash
   git clone <repo-url>
   cd AlgoVisual
   ```
2. Install dependencies:
   ```bash
   npm install
   ```
3. Start the server:
   ```bash
   npm start
   ```
4. Open browser:
   `http://localhost:3000`

## Notes

- The `runAlgorithm` function in `index.html` sends `GET /run?algo=<name>`.
- The four algorithm cards are wired to `dijkstra`, `bubble`, `selection`, `insertion`.
- Styling is based on custom gradients, transitions, and card hover effects.

## Contributing

- Open issues for bug reports and feature requests.
- Pull requests are welcome for UI polish, algorithm updates, and performance.

## License

MIT License (or choose your preferred license).
