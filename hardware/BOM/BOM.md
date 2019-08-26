#### Create BOM files for the equipment


We recommend creating different files:

<br>
- Electronic_BOM.csv: table containing all the integrated circuits(IC) necessary to populate the PCB (when one is present). We suggest using the format used by [kitspace.org](kitspace.org), so that people can easily order parts from different manufacturers.
<br>


| Reference | Qty  | Description | manufacturer  | MPN | Digikey | Mouser | RS | Newark | Farnell |
|---|---|---|---|---|---|---|---|---|---|
|Peltier element  |  1  | 12v 150w peltier TEC1-12715 | DUAITEK |  TEC1-12715  | -  | - |  -  |  -  |  peltiermodules.com  |
|  XTAL1 16 mhz  |  1  |  16 MHz crystal atmel328p |  ECS inc  |  ECS-160-20-4X  |  X1103-ND  |  520-160-20-4X-DU  |  -  |  -  |  -  |

<br>

- Mechanical_BOM.csv: Table containing all the mechanical parts necessary to build the equipment. Include here screws, printed parts, tubes, etc. See example below for fields

<br>

|part name| function  | quantity  |  obs.  |supplier|supplier number|link|
|---|---|---|---|---|---|---|
|M6x1 hex screws | used for holding motor in place  | 5  |  these could be substituted by flathead screws  |digikey| RPC6208-ND |https://www.digikey.co.uk/product-detail/en/essentra-components/SHSM6L16A/RPC6208-ND/9343049 |

<br>

- Tools_BOM.csv: table containing all tools used for the build. Pliers, hammer, etc.

<br>

|part name| function  | quantity  |  obs.  |supplier|supplier number|link|
|---|---|---|---|---|---|---|
|Nose needle Pliers  | hold components while soldering  | 1  |    regular pliers would also work   |digikey|L4VN-ND  |https://www.digikey.co.uk/product-detail/en/apex-tool-group/L4VN/L4VN-ND/8021129 |
