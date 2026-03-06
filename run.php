<?php
$algo = isset($_GET['algo']) ? strtolower(trim($_GET['algo'])) : '';

$executables = [
    'bubble' => 'bubblesort.exe',
    'selection' => 'selection.exe',
    'insertion' => 'insertion.exe',
    'dijkstra' => 'Dijestra.exe'
];

if (!array_key_exists($algo, $executables)) {
    echo '<div class="status">Invalid algorithm.</div>Use: bubble, selection, insertion, dijkstra.';
    exit;
}

$exePath = __DIR__ . DIRECTORY_SEPARATOR . $executables[$algo];

if (!file_exists($exePath)) {
    echo '<div class="status">Executable not found:</div>' . htmlspecialchars($executables[$algo]);
    exit;
}

shell_exec('"' . $exePath . '"');

echo '<div class="status">' . ucfirst($algo) . ' executed successfully.</div>';
echo 'Program: ' . htmlspecialchars($executables[$algo]);
?>
