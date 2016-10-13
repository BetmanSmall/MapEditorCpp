<?xml version="1.0" encoding="UTF-8"?>
<tileset name="tower6_test1x1" tilewidth="64" tileheight="64" tilecount="1" columns="1">
 <properties>
  <property name="ammoDistance" value="5"/>
  <property name="ammoSize" value="0.5"/>
  <property name="ammoSpeed" value="0.1"/>
  <property name="cost" value="10"/>
  <property name="damage" value="7"/>
  <property name="factionName" value="Faction1"/>
  <property name="name" value="Test1x1"/>
  <property name="radius" value="1"/>
  <property name="reloadTime" value="0.4"/>
  <property name="size" value="1"/>
  <property name="type" value="tower"/>
 </properties>
 <image source="../../textures/tower1x1.png" trans="ff00ff" width="64" height="64"/>
 <terraintypes>
  <terrain name="idle_UP" tile="0"/>
 </terraintypes>
 <tile id="0">
  <properties>
   <property name="tileName" value="idleTile"/>
  </properties>
 </tile>
</tileset>
