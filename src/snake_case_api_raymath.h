// generated with rlparser, go to raylib/tools/rlparser, put this instead of `case CODE: break;`:
/*
        case CODE:
        {
            for (int i = 0; i < funcCount; i++)
            {
                const char* fn_name = funcs[i].name;
                fprintf(outFile, "#define ");
                fputc(fn_name[0] - 'A' + 'a', outFile);
                for (int i=1; fn_name[i]!='\0'; ++i) {
                  char c = fn_name[i];
                  if (c>='A' && c<='Z') {
                    fputc('_', outFile);
                    fputc(c - 'A' + 'a', outFile);
                  } else {
                    fputc(c, outFile);
                  }
                }
                fprintf(outFile, " %s\n", fn_name);
            }
        } break;
*/
// then run command: make && ./rlparser -i ../../src/raymath.h -f CODE -d RMAPI -o raymath_snake_case.h

#define clamp Clamp
#define lerp Lerp
#define normalize Normalize
#define remap Remap
#define wrap Wrap
#define float_equals FloatEquals
#define vector2_zero Vector2Zero
#define vector2_one Vector2One
#define vector2_add Vector2Add
#define vector2_add_value Vector2AddValue
#define vector2_subtract Vector2Subtract
#define vector2_subtract_value Vector2SubtractValue
#define vector2_length Vector2Length
#define vector2_length_sqr Vector2LengthSqr
#define vector2_dot_product Vector2DotProduct
#define vector2_cross_product Vector2CrossProduct
#define vector2_distance Vector2Distance
#define vector2_distance_sqr Vector2DistanceSqr
#define vector2_angle Vector2Angle
#define vector2_line_angle Vector2LineAngle
#define vector2_scale Vector2Scale
#define vector2_multiply Vector2Multiply
#define vector2_negate Vector2Negate
#define vector2_divide Vector2Divide
#define vector2_normalize Vector2Normalize
#define vector2_transform Vector2Transform
#define vector2_lerp Vector2Lerp
#define vector2_reflect Vector2Reflect
#define vector2_min Vector2Min
#define vector2_max Vector2Max
#define vector2_rotate Vector2Rotate
#define vector2_move_towards Vector2MoveTowards
#define vector2_invert Vector2Invert
#define vector2_clamp Vector2Clamp
#define vector2_clamp_value Vector2ClampValue
#define vector2_equals Vector2Equals
#define vector2_refract Vector2Refract
#define vector3_zero Vector3Zero
#define vector3_one Vector3One
#define vector3_add Vector3Add
#define vector3_add_value Vector3AddValue
#define vector3_subtract Vector3Subtract
#define vector3_subtract_value Vector3SubtractValue
#define vector3_scale Vector3Scale
#define vector3_multiply Vector3Multiply
#define vector3_cross_product Vector3CrossProduct
#define vector3_perpendicular Vector3Perpendicular
#define vector3_length Vector3Length
#define vector3_length_sqr Vector3LengthSqr
#define vector3_dot_product Vector3DotProduct
#define vector3_distance Vector3Distance
#define vector3_distance_sqr Vector3DistanceSqr
#define vector3_angle Vector3Angle
#define vector3_negate Vector3Negate
#define vector3_divide Vector3Divide
#define vector3_normalize Vector3Normalize
#define vector3_project Vector3Project
#define vector3_reject Vector3Reject
#define vector3_ortho_normalize Vector3OrthoNormalize
#define vector3_transform Vector3Transform
#define vector3_rotate_by_quaternion Vector3RotateByQuaternion
#define vector3_rotate_by_axis_angle Vector3RotateByAxisAngle
#define vector3_move_towards Vector3MoveTowards
#define vector3_lerp Vector3Lerp
#define vector3_cubic_hermite Vector3CubicHermite
#define vector3_reflect Vector3Reflect
#define vector3_min Vector3Min
#define vector3_max Vector3Max
#define vector3_barycenter Vector3Barycenter
#define vector3_unproject Vector3Unproject
#define vector3_to_float_v Vector3ToFloatV
#define vector3_invert Vector3Invert
#define vector3_clamp Vector3Clamp
#define vector3_clamp_value Vector3ClampValue
#define vector3_equals Vector3Equals
#define vector3_refract Vector3Refract
#define vector4_zero Vector4Zero
#define vector4_one Vector4One
#define vector4_add Vector4Add
#define vector4_add_value Vector4AddValue
#define vector4_subtract Vector4Subtract
#define vector4_subtract_value Vector4SubtractValue
#define vector4_length Vector4Length
#define vector4_length_sqr Vector4LengthSqr
#define vector4_dot_product Vector4DotProduct
#define vector4_distance Vector4Distance
#define vector4_distance_sqr Vector4DistanceSqr
#define vector4_scale Vector4Scale
#define vector4_multiply Vector4Multiply
#define vector4_negate Vector4Negate
#define vector4_divide Vector4Divide
#define vector4_normalize Vector4Normalize
#define vector4_min Vector4Min
#define vector4_max Vector4Max
#define vector4_lerp Vector4Lerp
#define vector4_move_towards Vector4MoveTowards
#define vector4_invert Vector4Invert
#define vector4_equals Vector4Equals
#define matrix_determinant MatrixDeterminant
#define matrix_trace MatrixTrace
#define matrix_transpose MatrixTranspose
#define matrix_invert MatrixInvert
#define matrix_identity MatrixIdentity
#define matrix_add MatrixAdd
#define matrix_subtract MatrixSubtract
#define matrix_multiply MatrixMultiply
#define matrix_multiply_value MatrixMultiplyValue
#define matrix_translate MatrixTranslate
#define matrix_rotate MatrixRotate
#define matrix_rotate_x MatrixRotateX
#define matrix_rotate_y MatrixRotateY
#define matrix_rotate_z MatrixRotateZ
#define matrix_rotate_x_y_z MatrixRotateXYZ
#define matrix_rotate_z_y_x MatrixRotateZYX
#define matrix_scale MatrixScale
#define matrix_frustum MatrixFrustum
#define matrix_perspective MatrixPerspective
#define matrix_ortho MatrixOrtho
#define matrix_look_at MatrixLookAt
#define matrix_to_float_v MatrixToFloatV
#define quaternion_add QuaternionAdd
#define quaternion_add_value QuaternionAddValue
#define quaternion_subtract QuaternionSubtract
#define quaternion_subtract_value QuaternionSubtractValue
#define quaternion_identity QuaternionIdentity
#define quaternion_length QuaternionLength
#define quaternion_normalize QuaternionNormalize
#define quaternion_invert QuaternionInvert
#define quaternion_multiply QuaternionMultiply
#define quaternion_scale QuaternionScale
#define quaternion_divide QuaternionDivide
#define quaternion_lerp QuaternionLerp
#define quaternion_nlerp QuaternionNlerp
#define quaternion_slerp QuaternionSlerp
#define quaternion_cubic_hermite_spline QuaternionCubicHermiteSpline
#define quaternion_from_vector3_to_vector3 QuaternionFromVector3ToVector3
#define quaternion_from_matrix QuaternionFromMatrix
#define quaternion_to_matrix QuaternionToMatrix
#define quaternion_from_axis_angle QuaternionFromAxisAngle
#define quaternion_to_axis_angle QuaternionToAxisAngle
#define quaternion_from_euler QuaternionFromEuler
#define quaternion_to_euler QuaternionToEuler
#define quaternion_transform QuaternionTransform
#define quaternion_equals QuaternionEquals
#define matrix_compose MatrixCompose
#define matrix_decompose MatrixDecompose
