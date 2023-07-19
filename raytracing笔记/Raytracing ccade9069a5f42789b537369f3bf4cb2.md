# Raytracing

## 光线

假定光线公式为

$$
\mathbf{p}(t)=\mathbf{a}+t \overrightarrow{\mathbf{b}}
$$

p是三维射线上的一个点，a为射线原点，向量b是射线方向，t是实数，p接受任意t为变量返回射线上对应点（t≥0）.

光线追踪器的的核心是从像素发射射线并且计算这些射线得到的颜色：

1.将射线从视点转化为像素坐标

2.计算光线是否与场景中物体相交

3.若相交，计算交点颜色

## 球体

将球面方程写成向量形式,对球面上点p，有$(p-c)*(p-c)=R^2$

如果射线与球体相交，则存在一个t使得p(t)满足球面方程

![Untitled](Raytracing%20ccade9069a5f42789b537369f3bf4cb2/Untitled.png)

最后得到一个关于t的一元二次方程，可利用求根公式求解

## 法线

首先我们应该知道光线与物体相交的坐标，得到坐标后，可以简单的用坐标减去球心并单位化得到该点的法线

## 反走样

首先使用一个随机数生成函数，返回0到1的随机数，在发射光线时每次发射的光线不再是从像素中心发出采样了一个方形区域中的所有颜色再平均，MSAA，用来消除边缘的锯齿

## 漫反射

> 漫反射材质不仅仅接受其周围环境的光线, 还会在散射时使光线变成自己本身的颜色。光线射入漫反射材质后, 其反射方向是随机的。
> 

这里是让散射的光线随机发射出去，对生成的散射光线再追踪颜色，并且乘一个衰减率，加一个递归次数。在阴影部分的光线会不断反射再碰到物体导致光被吸收。

## 相机

fov 视角 一般使用垂直方向的fov  

![Untitled](Raytracing%20ccade9069a5f42789b537369f3bf4cb2/Untitled%201.png)

这个值决定了光线会发射到多大的范围中去，范围越小会让物体显得越大，相机需要用三个向量描述

![Untitled](Raytracing%20ccade9069a5f42789b537369f3bf4cb2/Untitled%202.png)

从相机位置和相机看的方向得到lookat向量，与vup叉乘就可以得到右边向量u，再叉乘得到v

## 散焦模糊

所有光线都从内部一个虚拟透镜随机发出，透镜与平面距离为焦距，透镜大小相对于光圈

这样在焦平面的物体所有光线都会采样到一个点上，所以成像清晰，不在焦平面的点由于采样范围变大会模糊

## 动态模糊

对于每一条光线储存一个时间变量，在计算物体相交时用这个时间来判断物体位置计算颜色再平均

## BVH

对于x，y，z平面来说，可以求得射线与平面相交的点坐标，即之前的变量t，对三个平面相交的变量t进行范围是否重叠进行判断，可以判断射线是否与平面形成的矩形包围盒相交

使用max和min函数来规避除数为0的情况

```cpp
bvh_node::bvh_node(
    std::vector<shared_ptr<hittable>>& objects,
    size_t start, size_t end, double time0, double time1
) {
    int axis = random_int(0,2);
    auto comparator = (axis == 0) ? box_x_compare
                    : (axis == 1) ? box_y_compare
                                  : box_z_compare;//自定义比较器

    size_t object_span = end - start;

    if (object_span == 1) {//只剩一个  左右都存
        left = right = objects[start];
    } else if (object_span == 2) {//只剩两个  按轴分到左右
        if (comparator(objects[start], objects[start+1])) {
            left = objects[start];
            right = objects[start+1];
        } else {
            left = objects[start+1];
            right = objects[start];
        }
    } else {//如果有两个以上物体
        std::sort(objects.begin() + start, objects.begin() + end, comparator);
//按某一轴排序
        auto mid = start + object_span/2;//中间分开
        left = make_shared<bvh_node>(objects, start, mid, time0, time1);
        right = make_shared<bvh_node>(objects, mid, end, time0, time1);
    }

    aabb box_left, box_right;

    if (  !left->bounding_box (time0, time1, box_left)
       || !right->bounding_box(time0, time1, box_right)
    )
        std::cerr << "No bounding box in bvh_node constructor.\n";

    box = surrounding_box(box_left, box_right);//生成一个总包围盒
}
```

## 纹理,贴图

使用stbi_load来读取贴图，将一个uv坐标系映射到贴图上

## 光源

不发生散射，只返回一个颜色值的材质，光线追踪到光源时便会累加光源的颜色

## 体积体

固定密度的体积体，光线在体积内部散射或者直接传过去，当光线射入体积体时可能在任意一点发生散射

![Untitled](Raytracing%20ccade9069a5f42789b537369f3bf4cb2/Untitled%203.png)

c是体积体的光学密度比例常数

```cpp
bool constant_medium::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    // Print occasional samples when debugging. To enable, set enableDebug true.
    const bool enableDebug = false;
    const bool debugging = enableDebug && random_double() < 0.00001;

    hit_record rec1, rec2;

    if (!boundary->hit(r, -infinity, infinity, rec1))//这里给rec1 2赋值了
        return false;

    if (!boundary->hit(r, rec1.t+0.0001, infinity, rec2))
        return false;

    if (debugging) std::cerr << "\nt0=" << rec1.t << ", t1=" << rec2.t << '\n';

    if (rec1.t < t_min) rec1.t = t_min;
    if (rec2.t > t_max) rec2.t = t_max;

    if (rec1.t >= rec2.t)
        return false;

    if (rec1.t < 0)
        rec1.t = 0;

    const auto ray_length = r.direction().length();//光线总长
    const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;//时间间隔内走的长度
    const auto hit_distance = neg_inv_density * log(random_double());//随机长度

    if (hit_distance > distance_inside_boundary)//随机长度大于走的长度，光线直接弹射出去
        return false;

    rec.t = rec1.t + hit_distance / ray_length;//否则从随机长度的碰撞点开始继续散射
    rec.p = r.at(rec.t);

    if (debugging) {
        std::cerr << "hit_distance = " <<  hit_distance << '\n'
                  << "rec.t = " <<  rec.t << '\n'
                  << "rec.p = " <<  rec.p << '\n';
    }

    rec.normal = vec3(1,0,0);  // arbitrary
    rec.front_face = true;     // also arbitrary
    rec.mat_ptr = phase_function;

    return true;
}
```