typedef pair<int, int> pii;

int cross(const pii &O, const pii &A, const pii &B) {
    return (A.first - O.first) * (B.second - O.second) - 
           (A.second - O.second) * (B.first - O.first);
}

vector<pii> convexHull(vector<pii> points) {
    if (points.size() <= 1) return points;

    sort(points.begin(), points.end());
    vector<Point> hull;

    for (const auto &p : points) {
        while (hull.size() >= 2 && cross(hull[hull.size()-2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }

    int lower_size = hull.size();
    for (int i = points.size() - 2; i >= 0; --i) {
        while ((int)hull.size() > lower_size && cross(hull[hull.size()-2], hull.back(), points[i]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    hull.pop_back();
    return hull;
}