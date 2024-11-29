import streamlit as st
import math
import random
from typing import List

class Point:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

closest_pair = [None, None]

def calculate_distance(p1: Point, p2: Point) -> float:
    return math.sqrt((p1.x - p2.x) ** 2 + (p1.y - p2.y) ** 2)

def brute_force_closest(points: List[Point]) -> float:
    global closest_pair
    min_distance = float('inf')
    n = len(points)
    for i in range(n):
        for j in range(i + 1, n):
            dist = calculate_distance(points[i], points[j])
            if dist < min_distance:
                min_distance = dist
                closest_pair[0], closest_pair[1] = points[i], points[j]
    return min_distance

def closest_in_strip(strip: List[Point], d: float) -> float:
    global closest_pair
    strip.sort(key=lambda p: p.y)
    min_distance = d
    for i in range(len(strip)):
        for j in range(i + 1, len(strip)):
            if (strip[j].y - strip[i].y) < min_distance:
                dist = calculate_distance(strip[i], strip[j])
                if dist < min_distance:
                    min_distance = dist
                    closest_pair[0], closest_pair[1] = strip[i], strip[j]
    return min_distance

def closest_pair_recursive(points: List[Point]) -> float:
    if len(points) <= 3:
        return brute_force_closest(points)
   
    mid = len(points) // 2
    mid_point = points[mid]

    dl = closest_pair_recursive(points[:mid])
    dr = closest_pair_recursive(points[mid:])
    d = min(dl, dr)

    strip = [p for p in points if abs(p.x - mid_point.x) < d]
    return min(d, closest_in_strip(strip, d))

def find_closest(points: List[Point]) -> float:
    points.sort(key=lambda p: p.x)
    return closest_pair_recursive(points)

st.title("Closest Pair of Points")
st.sidebar.title("Settings")
# Add custom CSS for colors and styling
st.markdown(
    """
    <style>
    .main-title {
        font-size: 2em;
        color: #4CAF50;
        text-align: center;
        margin-bottom: 20px;
    }
    .file-title {
        font-size: 1.5em;
        color: #FF5722;
    }
    .distance-text {
        font-size: 1.2em;
        color: #2196F3;
    }
    .points-text {
        font-size: 1.2em;
        color: #673AB7;
    }
    .custom-button {
        background-color: #4CAF50; /* Green */
        border: none;
        color: white;
        padding: 10px 20px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 16px;
        margin: 4px 2px;
        cursor: pointer;
        border-radius: 8px;
    }
    .custom-checkbox {
        font-size: 1.2em;
        color: #FF9800;
    }
    </style>
    """,
    unsafe_allow_html=True,
)


# Generate random files
if 'generated_files' not in st.session_state:
    st.session_state.generated_files = []
    for i in range(10):
        num_points = random.randint(10, 50)
        points = [Point(random.randint(0, 1000), random.randint(0, 1000)) for _ in range(num_points)]
        st.session_state.generated_files.append(points)

file_index = st.sidebar.selectbox(
    "Select a file to process:",
    [f"file{i}" for i in range(len(st.session_state.generated_files))]
)

# Add a custom button for file processing
if st.sidebar.markdown('<button class="custom-button">Process File</button>', unsafe_allow_html=True):
    selected_points = st.session_state.generated_files[int(file_index[-1])]
    smallest_distance = find_closest(selected_points)
    p1, p2 = closest_pair

    st.markdown(f'<div class="file-title">Selected File: {file_index}</div>', unsafe_allow_html=True)
    st.markdown(f'<div class="distance-text">The smallest distance is: <b>{smallest_distance:.2f}</b></div>', unsafe_allow_html=True)
    st.markdown(
        f'<div class="distance-text">The closest pair of points is: <b>({p1.x}, {p1.y})</b> and <b>({p2.x}, {p2.y})</b></div>',
        unsafe_allow_html=True,
    )

# Checkbox to show points
if st.sidebar.checkbox("Show Points in File"):
    st.markdown(f'<div class="points-text">### Points in {file_index}</div>', unsafe_allow_html=True)
    for point in st.session_state.generated_files[int(file_index[-1])]:
        st.write(f"({point.x}, {point.y})")
