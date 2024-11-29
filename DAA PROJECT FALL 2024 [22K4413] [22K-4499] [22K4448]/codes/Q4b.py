import os
import random
import math
import streamlit as st
# Custom CSS for button styling
st.markdown(
    """
    <style>
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
    .custom-button-red{
        background-color: #f44336; 
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
    </style>
    """,
    unsafe_allow_html=True
)

def gen_file_name(idx):
    return f"file_{idx + 1}.txt"

def create_files():
    random.seed()
    n_nums = random.randint(50, 150) 
    for i in range(20):
        fname = gen_file_name(i)
        with open(fname, "w") as f:
            for _ in range(n_nums):
                f.write(f"{random.randint(10, 209)}\n")
    return n_nums 

def karatsuba(x, y):
    if x < 10 or y < 10:  # Base case
        return x * y

    n = max(len(str(x)), len(str(y)))
    half = n // 2
    high1, low1 = divmod(x, 10 ** half)
    high2, low2 = divmod(y, 10 ** half)

    z1 = karatsuba(high1, high2)
    z2 = karatsuba(low1, low2)
    z3 = karatsuba(high1 + low1, high2 + low2)

    return z1 * (10 ** (2 * half)) + (z3 - z1 - z2) * (10 ** half) + z2

st.title("Karatsuba Multiplication")
st.sidebar.title("File Operations")
# Add colored button for generating files
if st.sidebar.markdown('<button class="custom-button">Generate Random Files</button>', unsafe_allow_html=True):
    n_nums = create_files()
    st.sidebar.success(f"20 files created with {n_nums} random numbers each.")

file_list = [gen_file_name(i) for i in range(20) if os.path.exists(gen_file_name(i))]
if file_list:
    st.sidebar.write("Available Files:")
    for f in file_list:
        st.sidebar.write(f)

file1 = st.sidebar.selectbox("Select File 1 for X values", file_list)
file2 = st.sidebar.selectbox("Select File 2 for Y values", file_list)

# Add colored button for processing files
if st.sidebar.markdown('<button class="custom-button-red">Process Selected Files</button>', unsafe_allow_html=True):
    if not file1 or not file2:
        st.error("Please select two valid files.")
    elif file1 == file2:
        st.error("Please select two different files.")
    else:
        x_vals = []
        y_vals = []
        results = []

        try:
            with open(file1, "r") as f1, open(file2, "r") as f2:
                x_lines = f1.readlines()
                y_lines = f2.readlines()

                for x_line, y_line in zip(x_lines, y_lines):
                    x = int(x_line.strip())
                    y = int(y_line.strip())
                    x_vals.append(x)
                    y_vals.append(y)

                    prod = karatsuba(x, y)
                    results.append(prod)

            with open("output.txt", "w") as out:
                for res in results:
                    out.write(f"{res}\n")

            st.success("Processing complete. Results saved in 'output.txt'.")
            st.write("### Results:")
            for r in results:
                st.write(r)
        except ValueError as e:
            st.error(f"Error processing files: {e}")
