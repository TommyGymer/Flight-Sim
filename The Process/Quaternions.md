### Definition
A Quaternion is defined as a 4D vector

$$
\begin{pmatrix}
i \\
j \\
k \\
w \\
\end{pmatrix}
$$

Where i, j and k can be imagined as a 3D vector with w as a rotation around this 3D vector

Each of these can take a value between -1 and 1; that is, a quaternion is a 4D unit vector

As raylib  makes use of axis-angle, it is relatively simple to convert between quaternions and the format required by raylib

[source for below equations](https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToAngle/index.htm)

---
### Quaternion to Axis-Angle

$$ \theta = 2 * \arccos(w) $$
$$ x = \frac{i}{\sqrt{1-w^2}} $$
$$ y = \frac{j}{\sqrt{1-w^2}} $$
$$ z = \frac{k}{\sqrt{1-w^2}} $$

---
### Axis-Angle to Quaternion

$$ w = \cos{\frac{\theta}{2}} $$
$$ i = x\sin{\frac{\theta}{2}} $$
$$ j = y\sin{\frac{\theta}{2}} $$
$$ k = z\sin{\frac{\theta}{2}} $$

---
### Multiplication

$$ w = w_1 w_2 - x_1 x_2 - y_1 y_2 - z_1 z_2 $$
$$ i = w_1 x_2 + x_1 w_2 + y_1 z_2 - z_1 y_2 $$
$$ j = w_1 y_2 - x_1 z_2 + y_1 w_2 + z_1 x_2 $$
$$ k = w_1 z_2 + x_1 y_2 - y_1 x_2 + z_1 w_2 $$