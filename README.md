EchoVerse phase-2    https://github.com/Skandar7002/Echo-Verse-2

یک سیستم گراف ‌محور برای یافتن بهینه‌ترین توالی گوش دادن پادکست‌ها

هدف پروژه:

طراحی و پیاده‌سازی سیستمی که با استفاده از تئوری گراف‌ها، کوتاه‌ترین و بهینه‌ترین مسیر را برای گوش دادن به مجموعه‌ای از پادکست‌ها پیشنهاد دهد.

 مدل مفهومی
- پادکست‌ها = رأس‌های گراف (Vertices)
- ارتباط موضوعی/ذهنی بین پادکست‌ها = یال‌های وزن‌دار (Weighted Edges)
- وزن یال = هزینه جابجایی ذهنی یا میزان شباهت موضوعی

ساختار داده‌
کلاس Graph:
- ماتریس مجاورت (Adjacency Matrix)
- تعداد رأس‌ها (Vertex Count)
- حداکثر ظرفیت (Max Capacity)

الگوریتم اصلی

- الگوریتم دایکسترا (Dijkstra's Algorithm)
- پیچیدگی زمانی: O(V²) (با ماتریس مجاورت)
- مناسب برای گراف‌های با یال‌های غیرمنفی

پیاده‌سازی کلاس Graph:

متدهای اصلی:

1. addPodcast(int id)
- افزودن پادکست جدید به سیستم
- گسترش خودکار ماتریس در صورت نیاز

2. addEdge(int p1, int p2, int weight)

- ایجاد ارتباط بین دو پادکست

- وزن: میزان شباهت موضوعی (هرچه کمتر = شباهت بیشتر)

3. dijkstra(int source)
- محاسبه کوتاه‌ترین مسیر از پادکست مبدأ
- نمایش مسیرهای کامل و هزینه نهایی

متدهای کمکی:
- resizeMatrix(): بزرگ کردن ماتریس به صورت پویا
- findMinDistance(): یافتن نزدیک‌ترین رأس بازدیدنشده
- printPath(): نمایش مسیر به صورت متنی

مثال:

سناریو: مجموعه پادکست‌های آموزشی

- پادکست 0: برنامه‌نویسی مقدماتی
- پادکست 1: ساختمان داده
- پادکست 2: الگوریتم‌ها
- پادکست 3: هوش مصنوعی
- پادکست 4: یادگیری ماشین
- پادکست 5: شبکه‌های عصبی

گراف ایجاد شده:

      addEdge(0, 1, 2);  // برنامه‌نویسی → ساختمان داده
      addEdge(1, 2, 1);  // ساختمان داده → الگوریتم‌ها
      addEdge(2, 3, 3);  // الگوریتم‌ها → هوش مصنوعی
      addEdge(3, 4, 2);  // هوش مصنوعی → یادگیری ماشین
      addEdge(4, 5, 1);  // یادگیری ماشین → شبکه‌های عصبی
      addEdge(0, 2, 4);  // ارتباط مستقیم
      addEdge(1, 3, 5);  // ارتباط جایگزین

رابط کاربری با منوی تعاملی:

      === Podcast Listening Path Optimizer ===
      1. Add Podcast
      2. Add Connection Between Podcasts
      3. Find Shortest Listening Paths
      4. Auto Test
      5. Exit
      Choice: _

نمونه خروجی:

Shortest paths from Podcast 0:
   
    To Podcast | Distance | Path

         1     |    2     | 0 -> 1
         2     |    3     | 0 -> 1 -> 2
         3     |    6     | 0 -> 1 -> 2 -> 3
         4     |    8     | 0 -> 1 -> 2 -> 3 -> 4
         5     |    9     | 0 -> 1 -> 2 -> 3 -> 4 -> 5

مراحل الگوریتم دایکسترا:

1. مقداردهی اولیه:
- فاصله مبدأ = 0
- فاصله سایر رأس‌ها = ∞
- همه رأس‌ها = بازدیدنشده
2. تکرار اصلی:
- انتخاب رأس با کمترین فاصله بازدیدنشده
- به‌روزرسانی فاصله همسایه‌ها
- علامت‌گذاری به عنوان بازدیدشده
3. تکرار تا پوشش تمام رأس‌ها

پیاده سازی الگوریتم دایکسترا:

      void Graph::dijkstra(int source) {
                                                 
      // آرایه‌های کمکی
      int* distances = new int[vertexCount];

      bool* visited = new bool[vertexCount];

      int* parents = new int[vertexCount];

    // مقداردهی اولیه
    for (int i = 0; i < vertexCount; i++) {
        distances[i] = std::numeric_limits<int>::max();
        visited[i] = false;
        parents[i] = -1;
    }
    
    distances[source] = 0;
    
    // حلقه اصلی الگوریتم
    for (int count = 0; count < vertexCount - 1; count++) {
        int u = findMinDistance(distances, visited);
        visited[u] = true;
        
        for (int v = 0; v < vertexCount; v++) {
            if (!visited[v] && adjacencyMatrix[u][v] != 0 &&
                distances[u] != INF && 
                distances[u] + adjacencyMatrix[u][v] < distances[v]) {
                distances[v] = distances[u] + adjacencyMatrix[u][v];
                parents[v] = u;
            }
        }
    }
    
    // نمایش نتایج
    printResults(distances, parents, source);
}

پیچیدگی زمانی:

افزودن پادکست:O(1)

افزودن یال:O(1)

دایکسترا:O(V²)

نمایش نتایج:O(V)


خروجی تست خودکار:

     === Starting Auto Test ===

      Adding podcasts 0-6...
      Adding connections between podcasts...

      Finding shortest paths from Podcast 0:

    To Podcast | Distance | Path

         1     |    2     | 0 -> 1
         2     |    3     | 0 -> 1 -> 2
         3     |    9     | 0 -> 1 -> 3
         4     |    6     | 0 -> 1 -> 2 -> 4
         5     |    11    | 0 -> 1 -> 2 -> 4 -> 6 -> 5
         6     |    8     | 0 -> 1 -> 2 -> 4 -> 6

      === Auto Test Completed ===

ساختار فایل ها:

      EchoVerse-2/
      ├── Graph.h           # رابط کلاس گراف
      ├── Graph.cpp         # پیاده‌سازی گراف و دایکسترا
      ├── main.cpp          # رابط کاربری و تست
      ├── README.md         # مستندات پروژه

توسعه دهندگان: مجتبی فهیم پور،امیر گریوانی 

درس: ساختمان داد ها و الگوریتم