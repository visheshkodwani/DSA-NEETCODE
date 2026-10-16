---
# Copy this file into a topic folder, e.g. arrays/kadane.md
# (files starting with "_" are never published)
title: Problem Name
layout: problem
parent: Arrays          # must match the topic's title exactly
nav_order: 2            # problem number within the topic
difficulty: Medium      # Easy | Medium | Hard
time: O(n)
space: O(1)
---

One-line problem statement.

{: .intuition }
> The key idea in a sentence or two.

## Dry run

<div class="viz">
<p class="viz-legend"><span class="hl">■ changed</span> · <span class="done">■ final</span></p>
{% include array.html v="7,4,1,5,3" label="start" %}
{% include array.html v="1,4,7,5,3" hl="0,2" done="0" label="step 1" note="what happened" %}
</div>

<!-- Trees, graphs, recursion, HLD/LLD: use a ```mermaid block (graph TD, sequenceDiagram, classDiagram, ...) -->

## Code

```cpp
// solution
```

{: .pitfall }
> Edge case or bug that bit you.

{: .revisit }
> What to remember next time / alternative approaches.
