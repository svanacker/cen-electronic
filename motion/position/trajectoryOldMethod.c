

/**
* Structure to store a curve.
*/
typedef struct {
    int direction;
    float angle;
    float radius;
    float distance;
} Curve;


/*
void computeLargeRadiusCurve(Curve *curve, float left, float right) {
    // min and max curve distance values
    float min, max;
    int c = compareFloat(fabs(left), fabs(right));
    switch (c) {
    case 0:
        // straight (abs(left) = abs(right))
        curve->angle = 0;
        curve->radius = FLT_MAX;
        curve->distance = left;
        curve->direction = LEFT;
        return;
    case 1:
        // turn right (abs(left) > abs(right))
        min = right;
        max = left;
        curve->direction = RIGHT;
        break;
    default:
        // turn left (abs(left) < abs(right))
        min = left;
        max = right;
        curve->direction = LEFT;
        break;
    }
    float theta = max - min;
    curve->angle = theta / width;
    curve->radius = fabs((width / 2.0f) * (max + min) / theta);
    curve->distance = curve->angle * curve->radius;
}
*/

/*
void computeNarrowRadiusCurve(Curve *curve, float left, float right) {
    // min and max curve distance values
    float max, min;
    int c = compareFloat(fabs(left), fabs(right));
    switch (c) {
    case 0:
        // straight (abs(left) = abs(right))
        curve->angle = 0;
        curve->radius = FLT_MAX;
        curve->distance = left;
        curve->direction = LEFT;
        return;
    case 1:
        // turn right (abs(left) > abs(right))
        max = left;
        min = right;
        curve->direction = RIGHT;
        break;
    default:
        // turn left (abs(left) < abs(right))
        min = left;
        max = right;
        curve->direction = LEFT;
        break;
    }
    float theta = fabs(min) + fabs(max);
    curve->angle = (theta / width) * getSign(max);
    curve->radius = (width / 2.0f) * (fabs(max) - fabs(min)) / theta;
    curve->distance = curve->angle * curve->radius;
}
*/

/**
* Computes the curve characteristics from the left and 
* right distances.
* @param curve the structure receiving the curve data
* @param left the left distance
* @param right the rights distance
*/
/*
void computeCurve(Curve *curve, float left, float right) {
    if (getSign(left) == getSign(right)) {
        // ICR is outside of the wheels
        computeLargeRadiusCurve(curve, left, right);
    } else {
        // ICR is between the wheels
        computeNarrowRadiusCurve(curve, left, right);
    }
}
*/

/**
* Updates the current position with the specified curve data.
* @param curve the curve data
*/
/*
void updatePosition(Curve *curve) {
    float d = curve->distance;
    float a = curve->angle;
    float r = curve->radius;

    // straight distance
    float sd;
    if (a != 0) {
        sd = fabs(2.0f * r * sinf(a / 2.0f));
    } else {
        sd = fabs(d);
    }

    // move from current location in robot coordinates
    float t = a / 2.0f;
    float dx = sd * cosf(t);
    float dy = sd * sinf(t);

    // TODO ne tient pas compte des angles supérieurs à PI / 2
    switch (curve->direction) {
    case LEFT:
        if (a < 0) {
            dx = -dx;
            dy = -dy;
        }
        break;
    case RIGHT:
        if (a > 0) {
            dy = -dy;
        } else {
            dx = -dx;
        }
        a = -a;
        break;
    }

    // final orientation
    float finalOrientation = fmodf(position.orientation + a, 2.0f * PI);

    Point end = {dx, dy};
    transform(&end, finalOrientation, position.pos);

    position.pos = end;
    position.orientation = finalOrientation;
}
*/


/**
* Computes and updates the position from the spécified 
* values from the coders.
* @param left the value of the left coder
* @param right the value of the right coder
* @return 1 if the position has been updated, 0 otherwise
*/
/*
int curveUpdateFromCoders(signed long left, signed long right) {
    Curve curve;
    float l = WHEEL_LENGTH_LEFT * left;
    float r = WHEEL_LENGTH_RIGHT * right;
    float dl = l - lastLeft;
    float dr = r - lastRight;
    if (fabs(dl) > UPDATE_THRESHOLD || fabs(dr) > UPDATE_THRESHOLD) {
        computeCurve(&curve, dl, dr);
        updatePosition(&curve);
        lastLeft = l;
        lastRight = r;
        return 1;
    }
    return 0;
}
*/
