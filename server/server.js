const express = require("express");
const path = require("path");
const fs = require("fs");
const { execFile } = require("child_process");

const app = express();
const port = process.env.PORT || 3000;
const rootDir = path.resolve(__dirname, "..");
const publicDir = path.join(rootDir, "public");
const binDir = path.join(rootDir, "native", "bin");

const executables = {
  bubble: "bubblesort.exe",
  selection: "selection.exe",
  insertion: "insertion.exe",
  dijkstra: "Dijestra.exe",
};

app.use(express.static(publicDir));

app.get("/run", (req, res) => {
  const algo = String(req.query.algo || "").toLowerCase().trim();

  if (!Object.prototype.hasOwnProperty.call(executables, algo)) {
    res.status(400).send("Invalid algorithm. Use: bubble, selection, insertion, dijkstra.");
    return;
  }

  const exePath = path.join(binDir, executables[algo]);
  if (!fs.existsSync(exePath)) {
    res.status(404).send(`Executable not found: ${executables[algo]}`);
    return;
  }

  execFile(exePath, (error) => {
    if (error) {
      res.status(500).send(`Failed to execute ${executables[algo]}`);
      return;
    }

    res.send(`${algo} executed successfully. Program: ${executables[algo]}`);
  });
});

app.listen(port, () => {
  console.log(`AlgoVisual server running on http://localhost:${port}`);
});
