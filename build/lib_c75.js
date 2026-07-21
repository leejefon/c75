// Bridges the C shim to the worker's blocking-input helpers (see site/worker.js).
// Everything here runs on the worker thread, so it is free to block on
// Atomics.wait until the main thread delivers a keystroke.
addToLibrary({
  c75_getch: function () {
    return C75.getch();
  },
  c75_kbhit: function () {
    return C75.kbhit();
  },
  c75_sleep: function (ms) {
    C75.sleep(ms);
  },
  c75_beep: function (freq, dur) {
    C75.beep(freq, dur);
  },
});
