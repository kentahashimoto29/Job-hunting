xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 51;
 0.00000;-0.75765;1.58563;,
 0.53575;-0.53575;1.58563;,
 0.53575;-0.53575;4.11848;,
 0.00000;-0.75765;4.11848;,
 0.75765;0.00000;1.58563;,
 0.75765;-0.00000;4.11848;,
 0.53575;0.53575;1.58563;,
 0.53575;0.53575;4.11848;,
 0.00000;0.75765;1.58563;,
 0.00000;0.75765;4.11848;,
 -0.53575;0.53575;1.58563;,
 -0.53575;0.53575;4.11848;,
 -0.75765;0.00000;1.58563;,
 -0.75765;-0.00000;4.11848;,
 -0.53575;-0.53575;1.58563;,
 -0.53575;-0.53575;4.11848;,
 0.00000;0.00000;1.58563;,
 0.00000;-0.00000;4.11848;,
 0.00000;0.00000;-0.00432;,
 0.20400;-0.20400;0.12573;,
 0.00000;-0.28850;0.12573;,
 0.28850;0.00000;0.12573;,
 0.20400;0.20400;0.12573;,
 0.00000;0.28850;0.12573;,
 -0.20400;0.20400;0.12573;,
 -0.28850;0.00000;0.12573;,
 -0.20400;-0.20400;0.12573;,
 0.37695;-0.37695;0.49603;,
 0.00000;-0.53310;0.49603;,
 0.53310;0.00000;0.49603;,
 0.37695;0.37695;0.49603;,
 0.00000;0.53310;0.49603;,
 -0.37695;0.37695;0.49603;,
 -0.53310;0.00000;0.49603;,
 -0.37695;-0.37695;0.49603;,
 0.49250;-0.49250;1.05018;,
 0.00000;-0.69650;1.05018;,
 0.69650;0.00000;1.05018;,
 0.49250;0.49250;1.05018;,
 0.00000;0.69650;1.05018;,
 -0.49250;0.49250;1.05018;,
 -0.69650;0.00000;1.05018;,
 -0.49250;-0.49250;1.05018;,
 0.53310;-0.53310;1.70388;,
 0.00000;-0.75390;1.70388;,
 0.75390;0.00000;1.70388;,
 0.53310;0.53310;1.70388;,
 0.00000;0.75390;1.70388;,
 -0.53310;0.53310;1.70388;,
 -0.75390;0.00000;1.70388;,
 -0.53310;-0.53310;1.70388;;
 
 56;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 3;16,1,0;,
 3;16,4,1;,
 3;16,6,4;,
 3;16,8,6;,
 3;16,10,8;,
 3;16,12,10;,
 3;16,14,12;,
 3;16,0,14;,
 3;17,3,2;,
 3;17,2,5;,
 3;17,5,7;,
 3;17,7,9;,
 3;17,9,11;,
 3;17,11,13;,
 3;17,13,15;,
 3;17,15,3;,
 3;18,19,20;,
 3;18,21,19;,
 3;18,22,21;,
 3;18,23,22;,
 3;18,24,23;,
 3;18,25,24;,
 3;18,26,25;,
 3;18,20,26;,
 4;20,19,27,28;,
 4;19,21,29,27;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,25,33,32;,
 4;25,26,34,33;,
 4;26,20,28,34;,
 4;28,27,35,36;,
 4;27,29,37,35;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,33,41,40;,
 4;33,34,42,41;,
 4;34,28,36,42;,
 4;36,35,43,44;,
 4;35,37,45,43;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,41,49,48;,
 4;41,42,50,49;,
 4;42,36,44,50;;
 
 MeshMaterialList {
  2;
  56;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.772000;0.238400;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.620800;0.448800;0.179200;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  48;
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.707107;-0.707107;-0.000000;,
  1.000000;0.000000;-0.000000;,
  0.707107;0.707107;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.707107;0.707107;0.000000;,
  -1.000000;0.000000;-0.000000;,
  -0.707107;-0.707107;-0.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.643590;-0.765371;,
  0.455089;-0.455089;-0.765368;,
  0.643589;-0.000000;-0.765371;,
  0.455088;0.455088;-0.765369;,
  0.000000;0.643588;-0.765372;,
  -0.455088;0.455088;-0.765369;,
  -0.643589;-0.000000;-0.765371;,
  -0.455089;-0.455089;-0.765368;,
  0.000000;-0.906233;-0.422779;,
  0.640805;-0.640805;-0.422774;,
  0.906233;-0.000000;-0.422778;,
  0.640805;0.640805;-0.422775;,
  0.000000;0.906233;-0.422779;,
  -0.640805;0.640805;-0.422775;,
  -0.906233;-0.000000;-0.422778;,
  -0.640805;-0.640805;-0.422774;,
  0.000000;-0.982484;-0.186345;,
  0.694722;-0.694721;-0.186344;,
  0.982485;-0.000000;-0.186343;,
  0.694722;0.694722;-0.186343;,
  0.000000;0.982485;-0.186343;,
  -0.694722;0.694722;-0.186343;,
  -0.982485;-0.000000;-0.186343;,
  -0.694722;-0.694721;-0.186344;,
  0.000000;-0.996166;-0.087484;,
  0.704396;-0.704396;-0.087485;,
  0.996166;-0.000000;-0.087484;,
  0.704396;0.704396;-0.087485;,
  0.000000;0.996166;-0.087484;,
  -0.704396;0.704396;-0.087485;,
  -0.996166;-0.000000;-0.087484;,
  -0.704396;-0.704396;-0.087485;;
  56;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,10,11;,
  3;0,12,10;,
  3;0,13,12;,
  3;0,13,13;,
  3;0,13,13;,
  3;0,12,13;,
  3;0,14,12;,
  3;0,11,14;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;15,17,16;,
  3;15,18,17;,
  3;15,19,18;,
  3;15,20,19;,
  3;15,21,20;,
  3;15,22,21;,
  3;15,23,22;,
  3;15,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,24,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,24,32,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,32,40,47;;
 }
}
