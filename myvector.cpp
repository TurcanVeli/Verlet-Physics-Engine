#include "myvector.h"



float MyVectorMath::magnetute(Vector2f A)
{
    return std::sqrt(A.x * A.x + A.y * A.y);
}


Vector2f MyVectorMath::distance(Vector2f A, Vector2f B)
{
    return A - B;
}


Vector2f MyVectorMath::normalize(Vector2f A)
{
    float M = magnetute(A);
    return Vector2f(A.x / M, A.y / M);
}


float MyVectorMath::dot(Vector2f A, Vector2f B)
{
    return A.x * B.x + A.y * B.y;
}


Vector2f MyVectorMath::cross(Vector2f A, Vector2f B)
{
    return Vector2f();
}
