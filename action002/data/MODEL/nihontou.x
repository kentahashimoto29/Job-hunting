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
 90;
 0.24460;-0.15024;-10.86134;,
 0.24460;0.80095;-10.86134;,
 -0.24460;0.80095;-10.86134;,
 -0.24460;-0.15024;-10.86134;,
 0.24460;1.56596;-49.32354;,
 0.24460;0.70530;-48.24658;,
 -0.24460;1.36950;-51.43756;,
 -0.24460;2.31597;-53.67685;,
 -0.24460;-0.00517;-47.13585;,
 -0.24460;0.50885;-49.40122;,
 -0.24460;0.70530;-48.24658;,
 -0.24460;1.56596;-49.32354;,
 -0.24460;-1.01520;-10.86134;,
 -0.24460;1.30917;-44.32485;,
 0.24460;1.30917;-44.32485;,
 0.24460;0.36271;-44.32485;,
 -0.24460;-0.49794;-44.32485;,
 -0.24460;0.36271;-44.32485;,
 -0.24460;1.02001;-36.76979;,
 0.24460;1.02001;-36.76979;,
 0.24460;0.06406;-36.76979;,
 -0.24460;-0.80522;-36.76979;,
 -0.24460;0.06406;-36.76979;,
 -0.24460;0.89036;-27.56492;,
 0.24460;0.89036;-27.56492;,
 0.24460;-0.06560;-27.56492;,
 -0.24460;-0.93488;-27.56492;,
 -0.24460;-0.06560;-27.56492;,
 -0.24460;0.76109;-18.85787;,
 0.24460;0.76109;-18.85787;,
 0.24460;-0.14835;-18.85787;,
 -0.24460;-0.97534;-18.85787;,
 -0.24460;-0.14835;-18.85787;,
 1.98699;-2.31597;-11.09990;,
 1.98699;2.27645;-11.09990;,
 1.98699;2.27645;-10.51742;,
 1.98699;-2.31597;-10.51742;,
 -1.98699;2.27645;-11.09990;,
 -1.98699;2.27645;-10.51742;,
 -1.98699;-2.31597;-11.09990;,
 -1.98699;-2.31597;-10.51742;,
 0.48272;-0.09125;-10.53245;,
 0.32751;0.54133;-10.53245;,
 0.32751;0.54133;0.72499;,
 0.48272;-0.09125;0.72499;,
 -0.04717;0.80334;-10.53245;,
 -0.04717;0.80334;0.72499;,
 -0.42187;0.54133;-10.53245;,
 -0.42187;0.54133;0.72499;,
 -0.57708;-0.09125;-10.53245;,
 -0.57708;-0.09125;0.72499;,
 -0.42187;-0.72382;-10.53245;,
 -0.42187;-0.72382;0.72499;,
 -0.04717;-0.98584;-10.53245;,
 -0.04717;-0.98584;0.72499;,
 0.32751;-0.72382;-10.53245;,
 0.32751;-0.72382;0.72499;,
 0.32182;0.53170;1.16503;,
 0.47466;-0.09125;1.16503;,
 -0.04717;0.78972;1.16503;,
 -0.41616;0.53170;1.16503;,
 -0.56900;-0.09125;1.16503;,
 -0.41616;-0.71419;1.16503;,
 -0.04717;-0.97223;1.16503;,
 0.32182;-0.71419;1.16503;,
 0.30556;0.50427;1.53799;,
 0.45168;-0.09125;1.53799;,
 -0.04717;0.75094;1.53799;,
 -0.39992;0.50427;1.53799;,
 -0.54603;-0.09125;1.53799;,
 -0.39992;-0.68677;1.53799;,
 -0.04717;-0.93344;1.53799;,
 0.30556;-0.68677;1.53799;,
 0.28125;0.46322;1.78721;,
 0.41729;-0.09125;1.78721;,
 -0.04717;0.69289;1.78721;,
 -0.37561;0.46322;1.78721;,
 -0.51165;-0.09125;1.78721;,
 -0.37561;-0.64573;1.78721;,
 -0.04717;-0.87539;1.78721;,
 0.28125;-0.64573;1.78721;,
 0.25258;0.41481;1.87473;,
 0.37674;-0.09125;1.87473;,
 -0.04717;0.62443;1.87473;,
 -0.34694;0.41481;1.87473;,
 -0.47109;-0.09125;1.87473;,
 -0.34694;-0.59731;1.87473;,
 -0.04717;-0.80693;1.87473;,
 0.25258;-0.59731;1.87473;,
 -0.04717;-0.09125;1.87473;;
 
 86;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;5,8,9,6;,
 4;8,10,6,9;,
 4;10,11,7,6;,
 3;7,11,4;,
 3;12,0,3;,
 4;13,14,4,11;,
 4;14,15,5,4;,
 4;15,16,8,5;,
 4;16,17,10,8;,
 4;17,13,11,10;,
 4;18,19,14,13;,
 4;19,20,15,14;,
 4;20,21,16,15;,
 4;21,22,17,16;,
 4;22,18,13,17;,
 4;23,24,19,18;,
 4;24,25,20,19;,
 4;25,26,21,20;,
 4;26,27,22,21;,
 4;27,23,18,22;,
 4;28,2,1,29;,
 4;28,29,24,23;,
 4;29,1,0,30;,
 4;29,30,25,24;,
 4;30,0,12,31;,
 4;30,31,26,25;,
 4;31,12,3,32;,
 4;31,32,27,26;,
 4;32,3,2,28;,
 4;32,28,23,27;,
 4;33,34,35,36;,
 4;34,37,38,35;,
 4;37,39,40,38;,
 4;39,33,36,40;,
 4;39,37,34,33;,
 4;36,35,38,40;,
 4;41,42,43,44;,
 4;42,45,46,43;,
 4;45,47,48,46;,
 4;47,49,50,48;,
 4;49,51,52,50;,
 4;51,53,54,52;,
 4;53,55,56,54;,
 4;55,41,44,56;,
 4;44,43,57,58;,
 4;43,46,59,57;,
 4;46,48,60,59;,
 4;48,50,61,60;,
 4;50,52,62,61;,
 4;52,54,63,62;,
 4;54,56,64,63;,
 4;56,44,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 4;74,73,81,82;,
 4;73,75,83,81;,
 4;75,76,84,83;,
 4;76,77,85,84;,
 4;77,78,86,85;,
 4;78,79,87,86;,
 4;79,80,88,87;,
 4;80,74,82,88;,
 3;82,81,89;,
 3;81,83,89;,
 3;83,84,89;,
 3;84,85,89;,
 3;85,86,89;,
 3;86,87,89;,
 3;87,88,89;,
 3;88,82,89;;
 
 MeshMaterialList {
  4;
  86;
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.702400;0.700000;0.238400;1.000000;;
   2.000000;
   0.400000;0.400000;0.400000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.166400;0.166400;0.166400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  113;
  0.927248;-0.325964;-0.184279;,
  0.000000;-0.000000;1.000000;,
  0.736307;-0.645764;-0.202091;,
  0.846623;-0.494535;-0.196633;,
  0.981644;-0.166030;-0.093863;,
  0.784389;-0.604975;-0.136892;,
  -1.000000;-0.000000;0.000000;,
  0.909234;-0.398897;-0.119059;,
  -1.000000;-0.000000;0.000000;,
  0.849096;-0.526301;-0.045203;,
  0.000000;0.998997;0.044776;,
  0.961579;-0.273523;-0.023492;,
  -1.000000;-0.000000;-0.000000;,
  0.870875;-0.491324;-0.013323;,
  0.000000;0.999658;0.026167;,
  0.967181;-0.253995;-0.006887;,
  -1.000000;-0.000000;0.000000;,
  0.868806;-0.495125;-0.005211;,
  0.000000;0.999895;0.014464;,
  0.966646;-0.256103;-0.002695;,
  -1.000000;-0.000000;0.000000;,
  0.865864;-0.500273;-0.002400;,
  0.000000;0.999988;0.004930;,
  0.965884;-0.258972;-0.001243;,
  -1.000000;-0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  1.000000;-0.000002;-0.000000;,
  0.825009;0.565120;-0.000000;,
  0.573069;0.819507;-0.000000;,
  -0.825002;0.565130;-0.000000;,
  -1.000000;-0.000002;-0.000000;,
  -0.825007;-0.565122;0.000000;,
  -0.573068;-0.819508;0.000000;,
  0.825014;-0.565111;0.000000;,
  0.999958;-0.000002;0.009153;,
  0.824962;0.565071;0.011520;,
  0.573019;0.819444;0.012674;,
  -0.824957;0.565078;0.011535;,
  -0.999958;-0.000002;0.009176;,
  -0.824963;-0.565068;0.011533;,
  -0.573027;-0.819439;0.012676;,
  0.824969;-0.565061;0.011517;,
  0.999203;-0.000001;0.039919;,
  0.824075;0.564254;0.050175;,
  0.572193;0.818262;0.055161;,
  -0.824073;0.564257;0.050177;,
  -0.999203;-0.000001;0.039921;,
  -0.824080;-0.564248;0.050173;,
  -0.572204;-0.818254;0.055155;,
  0.824082;-0.564244;0.050172;,
  0.995070;0.000000;0.099172;,
  0.819190;0.559905;0.124236;,
  0.567722;0.811843;0.136393;,
  -0.819188;0.559911;0.124218;,
  -0.995073;0.000000;0.099141;,
  -0.819191;-0.559909;0.124212;,
  -0.567712;-0.811852;0.136379;,
  0.819192;-0.559903;0.124230;,
  0.959428;0.000001;0.281952;,
  0.779424;0.524803;0.342169;,
  0.532347;0.761241;0.370297;,
  -0.779416;0.524809;0.342179;,
  -0.959425;0.000001;0.281963;,
  -0.779413;-0.524808;0.342187;,
  -0.532317;-0.761255;0.370311;,
  0.779421;-0.524802;0.342178;,
  0.907342;0.000002;0.420393;,
  0.721335;0.478319;0.500887;,
  0.000007;0.408918;0.912571;,
  -0.721317;0.478320;0.500911;,
  -0.907324;0.000001;0.420431;,
  -0.721307;-0.478311;0.500934;,
  0.000006;-0.408903;0.912578;,
  0.721324;-0.478309;0.500911;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  0.000000;0.985481;0.169784;,
  0.000000;0.993849;0.110741;,
  1.000000;0.000000;0.000000;,
  -1.000000;-0.000000;-0.000000;,
  -1.000000;-0.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  0.000000;0.999988;-0.004985;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  0.965816;-0.259230;-0.000666;,
  0.865599;-0.500736;-0.001287;,
  -1.000000;-0.000000;-0.000000;,
  -1.000000;-0.000000;-0.000000;,
  -1.000000;-0.000000;-0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.573049;0.819521;-0.000000;,
  -0.573004;0.819454;0.012680;,
  0.573089;-0.819493;0.000000;,
  0.573042;-0.819428;0.012669;,
  -0.572183;0.818269;0.055160;,
  0.572215;-0.818247;0.055156;,
  -0.567706;0.811855;0.136387;,
  0.567728;-0.811840;0.136386;,
  -0.532324;0.761255;0.370300;,
  0.532339;-0.761240;0.370309;;
  86;
  4;1,1,1,1;,
  4;4,7,3,0;,
  4;7,5,2,3;,
  4;76,8,77,78;,
  4;8,6,79,77;,
  3;80,81,81;,
  3;1,1,1;,
  4;10,10,81,81;,
  4;82,11,7,4;,
  4;11,9,5,7;,
  4;83,12,8,76;,
  4;12,84,6,8;,
  4;14,14,10,10;,
  4;85,15,11,82;,
  4;15,13,9,11;,
  4;86,16,12,83;,
  4;16,87,84,12;,
  4;18,18,14,14;,
  4;88,19,15,85;,
  4;19,17,13,15;,
  4;89,20,16,86;,
  4;20,90,87,16;,
  4;22,91,91,22;,
  4;22,22,18,18;,
  4;92,93,94,23;,
  4;92,23,19,88;,
  4;23,94,95,21;,
  4;23,21,17,19;,
  4;96,97,98,24;,
  4;96,24,20,89;,
  4;24,98,99,100;,
  4;24,100,90,20;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;101,101,101,101;,
  4;102,102,102,102;,
  4;1,1,1,1;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;103,31,39,104;,
  4;31,32,40,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;105,35,43,106;,
  4;35,28,36,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;104,39,47,107;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;106,43,51,108;,
  4;43,36,44,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;107,47,55,109;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;49,50,58,57;,
  4;108,51,59,110;,
  4;51,44,52,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;109,55,63,111;,
  4;55,56,64,63;,
  4;56,57,65,64;,
  4;57,58,66,65;,
  4;110,59,67,112;,
  4;59,52,60,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;111,63,71,70;,
  4;63,64,72,71;,
  4;64,65,73,72;,
  4;65,66,74,73;,
  4;112,67,75,74;,
  4;67,60,68,75;,
  3;1,1,1;,
  3;1,70,1;,
  3;70,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,74,1;,
  3;74,1,1;,
  3;1,1,1;;
 }
}
