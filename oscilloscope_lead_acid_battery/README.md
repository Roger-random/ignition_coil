# 12V Battery Under Oscilloscope
This directory hosts screen captures from my oscilloscope connected to the
output termiansl of a 12V lead acid battery as it provided power for my
coil test circuit.

---

![20ms/grid](./ignition%20coil%20on%20plug%2012V%20power%20draw%20fluctiation%2020_000us.png)

Zoomed out to 20ms per division covers three spark sequences. We see a voltage dip at each,
which I expected. But there's a tiny sliver of activity around that dip.

---

![500us/grid](./ignition%20coil%20on%20plug%2012V%20power%20draw%20fluctiation%20500us.png)

Zooming in to 500us per division (0.5ms per division) we see a single dip for a single spark
followed by voltage recovery. The tiny sliver is still very tiny.

---

![1us/grid](./ignition%20coil%20on%20plug%2012V%20power%20draw%20fluctiation%201us.png)

Zooming in further to 1us per division, we can see some shape to the tiny sliver.

---

![50ns/grid](./ignition%20coil%20on%20plug%2012V%20power%20draw%20fluctiation%2050ns.png)

We have to get all the way in to 50ns per division to see the shape in detail
and... I have no idea what I am looking at. Would this rise and fall come from
internal lead acid chemistry? The capacitors? Or was it feedback from something
else in the circuit? There's so much more to electronics I have yet to learn.
