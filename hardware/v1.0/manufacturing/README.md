<div align="center">

# HA Display: Hardware Assembly Guide

<img src="../../../images/HA-Display_v1.0.png" alt="Wiring" width="1000">

*PCB manufacturing, assembly, and hardware preparation guide*

</div>


This guide provides instructions for manufacturing and assembling the Home Assistant Display hardware. It assumes basic knowledge of soldering and printed circuit board assembly.


The KiCad project files are included in the `kicad` folder and contain the complete schematic and PCB layout. No KiCad knowledge is required to order the PCB, but the files are provided for reference and for anyone who wants to modify or manufacture the board independently.

I use [JLCPCB](https://jlcpcb.com) for PCB manufacturing and assembly, but the same production files should be compatible with other PCB manufacturers.

---

## Contents

- [1. Generate the Gerber and Drill Files](#1-generate-the-gerber-and-drill-files)
- [2. Generate BOM and Centroid Files](#2-generate-bom-and-centroid-files)
- [3. Order the Assembled PCBs from JLCPCB](#3-order-the-assembled-pcbs-from-jlcpcb)
- [4. Order the Additional Parts](#4-order-the-additional-parts)
- [5. Finish the PCB](#5-finish-the-pcb)
- [6. Inspect and Test the Hardware](#6-inspect-and-test-the-hardware)
- [7. Flash the Firmware](#7-flash-the-firmware)

---

## 1. Generate the Gerber and Drill Files

The first step is to export the Gerber and Drill files from KiCad for PCB manufacturing. See the [JLCPCB Gerber and Drill File Generation guide](https://jlcpcb.com/help/article/16-How-to-generate-Gerber-and-Drill-files-in-KiCad-6) for detailed instructions.

Alternatively, you can use the ready-made
[JLCPCB Gerber Files](HA-Display_v1.0_Gerbers.rar) included with this project.
Keep the files compressed when uploading them to JLCPCB.

## 2. Generate BOM and Centroid Files

To use JLCPCB's SMT Assembly service, the BOM and Centroid files are also
required. [Follow these instructions provided by JLCPCB](https://jlcpcb.com/help/article/81-How-to-generate-the-BOM-and-Centroid-file-from-KiCAD). 

Alternatively, you can use the ready-made files included with this project:

* [JLCPCB BOM](HA-Display_v1.0_BOM.csv).
* [JLCPCB Centroid file](HA-Display_v1.0-all-pos.csv).

## 3. Order the Assembled PCBs from JLCPCB

1. Have the Gerber, Drill, BOM, and Centroid files handy. (Keep the files zipped)
2. Visit the [JLCPCB Website](https://www.jlcpcb.com).
3. Click the **Order Now** button in the top menu bar.
4. Click the **Add Gerber File** button.

<div align="center">
<img src="../../../images/JLCPCB_Gerbers.png" alt="JLCPCB Gerbers Upload" width="1000">
</div>

5. Once [Gerber Files](HA-Display_v1.0_Gerbers.rar) are uploaded, you'll see the design in the viewer. You can adjust the PCB quantity you need in this step.

<div align="center">
<img src="../../../images/JLCPCB_PCB_Type.png" alt="JLCPCB Type" width="1000">
</div>

6. You can adjust **surface finish**. I personally prefer Black soldermask more than Green one, although you'll have to pay some extra money. Recommended to change the default HASL (with lead) to at least LeadFree HASL, as lead is toxic. If you want a better surface finish, select ENIG 1U".

<div align="center">
<img src="../../../images/JLCPCB_Surface_Finish.png" alt="JLCPCB Surface Finish" width="1000">
</div>

7. In the High-spec section, it's recommended to activate **Confirm Production file**. 

<div align="center">
<img src="../../../images/JLCPCB_Hi_Specs.png" alt="JLCPCB Hi specs" width="1000">
</div>

8. When **Confirm Production file** is activated, you'll be prompted whether to Confirm the file automatically after 48h. Mark the checkbox if you don't want your files to be confirmed automatically. Ensure you check your e-mail regularly to avoid any delays. 

<div align="center">
<img src="../../../images/JLCPCB_Confirm_PCB.png" alt="JLCPCB Confirm PCB" width="400">
</div>

9. Activate **PCB Assembly** section. Select the **Bottom side** to assemble the components. Adjust the quantity of Assembled PCB's you need. It's recommended to activate **Confirm Parts placement**. 

<div align="center">
<img src="../../../images/JLCPCB_PCB_Assy.png" alt="JLCPCB PCB Assembly" width="1000">
</div>

10. When **Confirm Parts placement** is activated, you'll be promted whether to Confirm the parts placement automatically after 72h. Mark the checkbox if you don't want parts placement to be confirmed automatically. Ensure you check your e-mail regularly to avoid any delays. 

<div align="center">
<img src="../../../images/JLCPCB_Confirm_Parts.png" alt="JLCPCB Confirm Parts" width="600">
</div>

11. Click **Next** in the right side bar. You'll get to the next page where you can see the PCB side it will be assembled. Click **Next** again to get to the next step.

<div align="center">
<img src="../../../images/JLCPCB_PCB_Assy_1.png" alt="JLCPCB Assembly" width="1000">
</div>

12. Click **Next** in the right side bar. You'll get to the next page where you must upload the [BOM](HA-Display_v1.0_BOM.csv) and [Centroid file](HA-Display_v1.0-all-pos.csv) files.

<div align="center">
<img src="../../../images/JLCPCB_BOM_CPL.png" alt="JLCPCB BOM CPL" width="1000">
</div>

13. Once BOM and CPL files are correctly uploaded, they will appear in each panel.

<div align="center">
<img src="../../../images/JLCPCB_BOM_CPL_ok.png" alt="JLCPCB BOM CPL OK" width="1000">
</div>

14. Click **Process BOM & CPL** button. It is normal for an error to appear because not all components are included in the assembly. This is expected for this design. Click **Continue** to proceed.

<div align="center">
<img src="../../../images/JLCPCB_BOM_CPL_Error.png" alt="JLCPCB BOM CPL Error" width="350">
</div>

15. Once BOM and CPL files are processed, you will see the **Bill of Materials** with the selected parts. Ensure all of them are checked before moving to the next step. In case some of the parts I sourced are not available, you can look for a replacement part in their [Parts Manager Page](https://jlcpcb.com/user-center/smtPrivateLibrary/). 

<div align="center">
<img src="../../../images/JLCPCB_BOM_Parts.png" alt="JLCPCB BOM Parts" width="1000">
</div>

16. In the next page you see the PCB with the **Components Placement**. Some of them may not be well positioned. You must adapt the position selecting the component to move and rotate or move it to the right placement according to the footprint. 

<div align="center">
<img src="../../../images/JLCPCB_Parts_Placement.png" alt="JLCPCB Parts Placement" width="1000">
</div>

In my case I've had to relocate:

* Power Switch.
* USB Type-C Connector.

*As these parts are Through Hole, it's easier to ensure proper placement from the Top Side of the PCB.*

<div align="center">
<img src="../../../images/JLCPCB_Parts_Placement_OK.png" alt="JLCPCB Parts Placement 1" width="1000">
</div>

> **Important:** Check the orientation of U2, U5 and U7 before approving the assembly. JLCPCB's placement data may require manual correction.

<div align="center">
<img src="../../../images/JLCPCB_Parts_Placement_NOK.png" alt="JLCPCB Parts Placement 2" width="1000">
</div>

Ensure the purple dot corresponds to the mark in the footprint (Pin #1).

<div align="center">
<img src="../../../images/JLCPCB_Parts_Placement_OK2.png" alt="JLCPCB Parts Placement 3" width="1000">
</div>

17. Once you ensured the right placement of all the parts, proceed to the next step **Quote & Order**. You'll see the Quotation of the PCB & Assembly. Select the **Product Description** in the right bar and click **Save to Cart** to move to the Cart page.

<div align="center">
<img src="../../../images/JLCPCB_Save_Cart_2pcs.png" alt="JLCPCB Save Cart" width="1000">
</div>

18. Select the Item to purchase in the **Shopping Cart** page. Shipping method can be selected in the right bar, it can be selected in the next step too.

<div align="center">
<img src="../../../images/JLCPCS_Shopping_Cart.png" alt="JLCPCB Checkout" width="1000">
</div>

19. I personally use **Global Standard Direct Line** when available, as it has generally provided a convenient shipping option for deliveries to Spain. Shipping options, taxes, duties, and availability may vary depending on the destination and current JLCPCB conditions.

<div align="center">
<img src="../../../images/JLCPCB_Shipping.png" alt="JLCPCB Shipping" width="600">
</div>

20. Select your shipping address and billing information.

<div align="center">
<img src="../../../images/JLCPCB_Checkout_2pcs_1.png" alt="JLCPCB Checkout 1" width="1000">
</div>

21. Select Shipping Method. **Global Standard Direct Line** is recommended.

<div align="center">
<img src="../../../images/JLCPCB_Checkout_2pcs_2.png" alt="JLCPCB Checkout 2" width="1000">
</div>

22. Select your preferred payment method and click **Submit Order**.

<div align="center">
<img src="../../../images/JLCPCB_Checkout_2pcs_3.png" alt="JLCPCB Checkout 3" width="1000">
</div>

23. Once your order is submitted and confirmed, you can track the status in the [Orders](https://jlcpcb.com/user-center/orders/) panel inside your account area.

Be ready to confirm PCB production and Parts Placement in your e-mail in case you checked those options.

> **Note:** The quoted price is provided for reference only. PCB and
> assembly costs can vary significantly depending on the selected
> specifications, quantity, components, and shipping method.
>
> For a lower-cost option, consider **Green soldermask** and
> **Economy PCB Assembly** where available.

## 4. Order the Additional Parts JLCPCB doesn't Assemble

There are a few parts that you will need to order yourself and solder on the PCBs after you receive them from JLCPCB.

Here is a list of the additional parts to order for the PCB:

* 1 × WeAct Studio 4.2" (400 × 300 px) three-color e-paper display.
* 1 × ESP32-S3-DevkitC-1.
* 2 × Momentary pushbuttons. [Würth Electronik 436331045822](https://octopart.com/es/part/wurth-elektronik/436331045822).
* 1 × DPDT Switch in case you used Economy PCB Assembly. [C&K OS202011MA0QN1](https://octopart.com/es/part/c-k-components/OS202011MA0QN1).
* 1 × 18650 Li-Ion Battery Holder & 18650 Cell.
* 2 × Female Headers 2.54mm 22-Pin Single Row for the ESP32-S3-DevkitC-1. *Optional but recommended*.
* 1 × Female Headers 2.54mm 4-Pin Single Row for the I2C expansion port. *Optional but recommended*.

## 5. Finish the PCB

Once you receive the assembled PCB from JLCPCB and the additional parts, install the remaining through-hole and mechanical components:

- ESP32-S3-DevKitC-1 headers.
- Pushbuttons.
- Battery holder.
- I2C expansion headers (optional).
- DPDT switch, if applicable.

After soldering all remaining components, the assembled PCB should look approximately like this:

<div align="center">

<img src="../../../images/HA-Display_v1.0_bottom.png"
     alt="HA Display assembled PCB"
     width="1000">

</div>

## 6. Inspect and Test the Hardware

Before installing the PCB into the enclosure, inspect all solder joints and component orientations.

Pay particular attention to:

- Power input and protection circuitry.
- ESP32-S3-DevKitC-1 orientation.
- BME688/BME680 orientation.
- Pushbutton operation.
- USB-C connector solder joints.
- Power switch orientation.
- Any manually assembled through-hole components.

Check for solder bridges or short circuits before connecting the battery.

## 7. Flash the Firmware to the ESP32-DevkitC-1

Before you attempt to get everything fitted into the enclosure, it's best to make sure all the hardware works.

Install the ESP32-DevkitC-1 into the headers on the PCB.

You'll need to compile the code and flash it into the ESP32-DevkitC-1 on the hardware. Instructions can be found [here](../../../firmware/README.md#installation).
